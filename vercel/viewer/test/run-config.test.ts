import assert from 'node:assert/strict';
import { describe, it } from 'node:test';
import { maxRunMs, sandboxVcpus } from '../api/_lib/run-config.ts';

describe('maxRunMs', () => {
  it('defaults to 15 minutes', () => {
    assert.equal(maxRunMs({}), 15 * 60_000);
  });
  it('reads NLT_RUN_MAX_MINUTES', () => {
    assert.equal(maxRunMs({ NLT_RUN_MAX_MINUTES: '30' }), 30 * 60_000);
  });
  it('never exceeds 60 minutes', () => {
    assert.equal(maxRunMs({ NLT_RUN_MAX_MINUTES: '600' }), 60 * 60_000);
  });
  it('falls back to the default for zero, negative or non-numeric values', () => {
    for (const bad of ['0', '-5', 'abc', '', ' ']) assert.equal(maxRunMs({ NLT_RUN_MAX_MINUTES: bad }), 15 * 60_000);
  });
});

describe('sandboxVcpus', () => {
  it('defaults to 2 vCPUs (4 GB)', () => {
    assert.equal(sandboxVcpus({}), 2);
  });
  it('reads NLT_SANDBOX_VCPUS', () => {
    assert.equal(sandboxVcpus({ NLT_SANDBOX_VCPUS: '1' }), 1);
    assert.equal(sandboxVcpus({ NLT_SANDBOX_VCPUS: '4' }), 4);
  });
  it('never exceeds 4 vCPUs', () => {
    assert.equal(sandboxVcpus({ NLT_SANDBOX_VCPUS: '16' }), 4);
  });
  it('falls back to the default for zero, negative or non-numeric values', () => {
    for (const bad of ['0', '-1', 'big', '']) assert.equal(sandboxVcpus({ NLT_SANDBOX_VCPUS: bad }), 2);
  });
});
