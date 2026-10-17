"""Run a Fusion module with its output appended to a log the Godot dock can read.

Usage: python -u launch_server.py <log_path> <module>

Why not just hold the log open: inside the editor Godot opens files for reading with
_SH_DENYWR (safe-save mode), which fails while any other process has the file open for
writing. A server holding its log open for its whole lifetime therefore made every dock
read return nothing, and the dock sat on "Waiting for uvicorn to bind..." forever.

So output goes through a pipe instead (fds 1 and 2 included, for native writes from
llama.cpp), and a daemon thread drains it, appending each chunk with the file opened and
closed per write. The pipe is always drained by this thread, never by the editor, so it
cannot fill and block the server (the original PeekNamedPipe hang).
"""

import os
import runpy
import sys
import threading
import time


def _append(path: str, data: bytes) -> None:
    # The dock's brief read open denies writers; retry rather than drop the line.
    for _ in range(50):
        try:
            with open(path, "ab") as log:
                log.write(data)
            return
        except PermissionError:
            time.sleep(0.02)


def _pump(read_fd: int, path: str) -> None:
    while True:
        chunk = os.read(read_fd, 65536)
        if not chunk:
            return
        _append(path, chunk)


def main() -> None:
    log_path, module = sys.argv[1], sys.argv[2]
    read_fd, write_fd = os.pipe()
    threading.Thread(target=_pump, args=(read_fd, log_path), daemon=True).start()
    os.dup2(write_fd, 1)
    os.dup2(write_fd, 2)
    sys.stdout = sys.stderr = os.fdopen(write_fd, "w", buffering=1, encoding="utf-8", errors="replace")
    sys.argv = sys.argv[:1]
    runpy.run_module(module, run_name="__main__", alter_sys=True)


if __name__ == "__main__":
    main()
