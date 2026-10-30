import test from "node:test";
import assert from "node:assert/strict";
import { buildHeadlessArgs } from "../src/headless.js";

test("headless run arguments are bounded and point at the configured project", () => {
  const args = buildHeadlessArgs(120);
  assert.ok(args.includes("--headless"));
  assert.ok(args.includes("--path"));
  assert.equal(args.at(-1), "120");
});

test("headless run rejects zero, fractional, and excessive iteration counts", () => {
  for (const value of [0, 1.5, 1_000_001]) {
    assert.throws(() => buildHeadlessArgs(value), /iterations/);
  }
});
