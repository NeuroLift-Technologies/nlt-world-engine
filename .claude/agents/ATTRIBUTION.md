# Attribution — imported Claude Code sub-agents

The 49 agent definition files in this directory (`*.md`, excluding this file) were
imported **verbatim** from a third-party, open-source project:

- **Source project:** Claude Code Game Studios
- **Upstream repo:** https://github.com/Donchitos/Claude-Code-Game-Studios
- **Imported at:** tag `v1.0.0`, commit `984023ddac0d5e27624f2baacde6105e45de375f`
- **License:** MIT (see full text below)
- **Imported into nlt-fusion:** 2026-06-19

These are the third-party project's own Claude Code sub-agent personas (a game-dev
"studio" hierarchy: directors, designers, programmers, QA, plus engine specialists
for Godot/Unity/Unreal). They were **not authored by NeuroLift Technologies** and are
not NLT governance artifacts. They are kept here as a reusable agent library for the
fusion simulation work; adaptation to the Python/web stack and the neurodivergent-first
sim domain is a separate follow-up.

> Note: ~15 of these are engine-specialist agents that assume Godot/Unity/Unreal and
> are not directly applicable to this repo's Python/web stack. They are retained for
> completeness per an explicit "keep them all" decision.

These files live under `.claude/agents/` (not the repo-root `agents/` directory) so
they remain separate from NLT's own `agents/*.md` Copilot profiles and their
governance frontmatter validation.

---

## MIT License (upstream)

```
MIT License

Copyright (c) 2026 Donchitos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
