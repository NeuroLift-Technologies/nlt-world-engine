# Architecture Diagrams

This directory contains architecture diagrams for the NLT World Engine.

## Files

- `training-architecture.html` — Interactive HTML diagram of the training loop
  (UE5 environment ↔ Python PPO brain ↔ TensorBoard logging). Open in any
  browser. Themes via CSS variables from the Hermes desktop app if embedded.

## Regenerating

These are hand-authored files. To modify, edit the source HTML directly.
If you add a new component to the system, update `training-architecture.html`
and re-check that all new connections are drawn in the diagram.

## Version History

| Date | Author | Changes |
|------|--------|---------|
| 2026-09-05 | Hermes | Initial training architecture diagram |
