"""Regression checks for the Fusion launcher's pipe and log lifecycle."""

import errno
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile
import textwrap
import unittest
from unittest.mock import patch


LAUNCHER = (
    Path(__file__).resolve().parents[1]
    / "world-engine-godot/addons/fusion_agent_loop/launch_server.py"
)
BOOTSTRAP = """
import importlib.util
import sys

spec = importlib.util.spec_from_file_location("launcher", sys.argv[1])
launcher = importlib.util.module_from_spec(spec)
spec.loader.exec_module(launcher)
{setup}
sys.argv = sys.argv[1:]
launcher.main()
"""


class LauncherTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.log = self.root / "server.log"

    def run_launcher(self, source, setup="", log=None):
        (self.root / "fixture_server.py").write_text(
            textwrap.dedent(source), encoding="utf-8"
        )
        return subprocess.run(
            [
                sys.executable,
                "-u",
                "-c",
                BOOTSTRAP.format(setup=textwrap.dedent(setup)),
                str(LAUNCHER),
                str(self.log if log is None else log),
                "fixture_server",
            ],
            cwd=self.root,
            capture_output=True,
            timeout=10,
        )

    def test_invalid_log_prevents_module_execution(self):
        result = self.run_launcher(
            "from pathlib import Path; Path('started').touch()", log=self.root
        )
        self.assertNotEqual(result.returncode, 0)
        self.assertFalse((self.root / "started").exists())
        self.assertIn(b"Error", result.stderr)

    def test_normal_exit_appends_and_flushes_python_and_native_output(self):
        self.log.write_bytes(b"previous log\n")
        result = self.run_launcher("""
            import os
            import sys
            os.write(1, b'native stdout\\n')
            os.write(2, b'native stderr\\n')
            sys.stdout.write('buffered tail')
        """)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(
            self.log.read_bytes(),
            b"previous log\nnative stdout\nnative stderr\nbuffered tail",
        )

    def test_startup_exception_drains_large_traceback_before_exit(self):
        result = self.run_launcher(
            """
            import sys
            sys.stdout.write('startup output\\n')
            raise RuntimeError('x' * 262144 + 'TRACEBACK END')
            """,
            setup="""
            import time
            append = launcher._append
            def slow_append(path, data):
                time.sleep(0.01)
                append(path, data)
            launcher._append = slow_append
            """,
        )
        self.assertNotEqual(result.returncode, 0)
        logged = self.log.read_bytes()
        self.assertTrue(logged.startswith(b"startup output\n"))
        self.assertIn(b"Traceback (most recent call last):", logged)
        self.assertIn(b"RuntimeError: " + b"x" * 262144 + b"TRACEBACK END\n", logged)

    def test_system_exit_preserves_status_and_buffered_output(self):
        result = self.run_launcher("""
            import sys
            sys.stderr.write('last message')
            raise SystemExit(7)
        """)
        self.assertEqual(result.returncode, 7, result.stderr)
        self.assertEqual(self.log.read_bytes(), b"last message")

    def test_system_exit_message_is_logged(self):
        result = self.run_launcher("raise SystemExit('startup failed')")
        self.assertEqual(result.returncode, 1)
        self.assertEqual(self.log.read_bytes(), b"startup failed\n")

    def test_log_write_failure_keeps_pipe_drained(self):
        result = self.run_launcher(
            """
            import os
            from pathlib import Path
            for _ in range(256):
                os.write(1, b'x' * 16384)
                os.write(2, b'y' * 16384)
            Path('finished').touch()
            """,
            setup="""
            import errno
            def fail_append(path, data):
                raise OSError(errno.ENOSPC, 'synthetic disk full')
            launcher._append = fail_append
            """,
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue((self.root / "finished").exists())

    def test_pump_resumes_logging_after_transient_failure_and_closes_reader(self):
        spec = importlib.util.spec_from_file_location("launcher", LAUNCHER)
        launcher = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(launcher)
        with (
            patch.object(launcher.os, "read", side_effect=[b"lost", b"saved", b""]),
            patch.object(launcher.os, "close") as close,
            patch.object(
                launcher, "_append", side_effect=[OSError(errno.ENOSPC, "full"), None]
            ) as append,
        ):
            launcher._pump(123, str(self.log))
        self.assertEqual(append.call_count, 2)
        append.assert_called_with(str(self.log), b"saved")
        close.assert_called_once_with(123)


if __name__ == "__main__":
    unittest.main()
