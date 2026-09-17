# Competitive programming templates

My C++ template library: pasteable, struct-encapsulated implementations of the
algorithms and data structures that actually come up in Codeforces/CSES/AtCoder
problems, plus the Vim setup (UltiSnips snippets, `.vimrc`, `cstart`) that pastes
them into a contest file fast.

Everything here is written to one rule: **nothing breaks when it's pasted into
the `normal` template, alone or combined with other templates from this repo.**
That's enforced two ways — every template is a self-contained `struct`/`namespace`
with zero global state (two structs with different names never collide; two
files with global `int n; vector<int> adj;` do), and every template has a real
test, not just an example that happens to work.

## Setup on a new machine

```
bash -c "$(curl -fsSL https://raw.githubusercontent.com/mdnihal5/competitive-programming/main/install.sh)"
```

Clones this repo to `~/Personal/competitive-programming` (the path the
snippets themselves resolve against), installs g++/astyle/a `+python3` Vim/a
clipboard tool via apt or Homebrew, bootstraps vim-plug, and **symlinks**
(not copies) `~/.vimrc` and `~/.vim/UltiSnips` at this repo's copies — so the
live config and the repo can never drift apart. Anything already at those
paths is backed up, never overwritten. Safe to re-run. `CP_SETUP_DRY_RUN=1`
previews every step without changing anything.

## Layout

```
Templete/       the base `normal` template, debug.hpp, PBDS
Graphs/         Dijkstra, Bellman-Ford, SCC, bridges/articulation, toposort,
                binary lifting (LCA/kth-ancestor), HLD, centroid decomp, Dinic, DSU
Trees/          weighted LCA
Strings/        Z-function, KMP, suffix array + LCP, Aho-Corasick, poly hashing
Maths/          ModInt, nCr/combinatorics, CRT, totient, fast pow + inverse, NTT, sieve
SegmentTree/    iterative segtree, lazy segtree, persistent segtree, merge sort
                tree, max-subarray segtree, range-toggle segtree
FenwickTree/    point-update, range-update point-query, range-update range-query
                (two-BIT trick), 2D
RMQ/            sparse table (1D + 2D), O(1) query
DP/             digit-DP / bitmask-DP / SOS-DP skeletons, D&C opt, Knuth's opt
Others/         min-stack, prefix/suffix mex, ternary search
vimrc/          copies of .vimrc, UltiSnips/cpp.snippets, UltiSnips/INDEX.md,
                bash_aliases -- the actual files this machine uses, mirrored here
tests/          run_all.sh -- compiles + runs every template's own test
```

## Using a template

**In an editor with the snippets installed** (see Vim setup below): open a
`.cpp` file, type `normal`, hit Tab — that's the base template. Then type any
trigger from `vimrc/UltiSnips/INDEX.md` (e.g. `DSU`, `SegTree`, `BinaryLift`)
and hit Tab again to paste that algorithm in. Triggers don't redeclare
`all`/`ALL`/`int`/`mod`/`N`/`inf`/`debug` — they assume `normal` already ran.

**Without the snippets**: open the relevant `.cpp` file in this repo directly.
Everything between `/* ---- SNIPPET START ---- */` and `/* ---- SNIPPET END ---- */`
is exactly what the UltiSnips trigger pastes — copy that block. Everything
outside those markers (includes, macros, the `#ifdef LOCAL_TEST` block) is the
file's own standalone test harness, not part of what gets pasted.

`vimrc/UltiSnips/INDEX.md` is the lookup — every trigger, a one-line description,
and a short usage example. `cpp.snippets` itself carries no comments by design
(fast to read mid-contest); the index is where the explanation lives. **Keep it
updated** whenever a snippet is added, renamed, or removed.

Forgot a trigger name mid-contest? Type `list`, hit Tab — it prints every
trigger + description as a comment block, right there in the file. It reads
`INDEX.md` at expansion time (same trick `normal` uses to resolve `debug.hpp`),
so it's never a stale copy of the index above it.

Only remember roughly what you want, not the exact name? Type a few letters,
then `<C-x><C-u>` — Vim's own completion, pointed at a custom function in
`vimrc/vimrc` that substring-matches (case-insensitive) against every trigger,
description and category in `INDEX.md`. Pick one, `<CR>` drops the real
trigger name at the cursor, then Tab expands it as usual. See `INDEX.md`'s
Meta section for the walkthrough.

## Testing

Every template has its own correctness test, compiled in via `-DLOCAL_TEST`,
living below the `SNIPPET END` marker in the same file — not a separate mirror
to keep in sync. Where a brute force is feasible (most graph/data-structure
algorithms), the test is a real stress test: hundreds of random small inputs
cross-checked against a trivial reference implementation, not one hand-picked
example. Run the whole suite:

```
tests/run_all.sh
```

It compiles and runs every `.cpp` file's `LOCAL_TEST` block and reports
pass/fail per file. Rerun it after editing any template.

## Vim setup

`vimrc/vimrc` is the actual `.vimrc` in use — cross-platform: it resolves the
right compiler automatically (`g++` on Linux; the newest Homebrew `g++-N` on
macOS, since macOS's own `g++` is Clang and has neither `bits/stdc++.h` nor PBDS)
and branches clipboard commands (`wl-copy`/`xclip` on Linux, `pbcopy` on macOS).

**One-time macOS setup** (Ubuntu needs nothing extra):
```
brew install gcc astyle
```
That installs real GNU g++ under `/opt/homebrew/bin` as `g++-N` — `bits/stdc++.h`
and `<ext/pb_ds/...>` (PBDS) both need actual GNU libstdc++, which Apple Clang's
libc++ doesn't provide, so this step isn't optional.

`vimrc/bash_aliases` has `cstart` — `cstart [dir] name...` creates empty `.cpp` +
`input.txt`/`output.txt` under `$CSTART_DIR` (default `~/contest`), opens the
first file in Vim. Type `normal<Tab>` for the template. Source it from
`.bashrc` (or `.zshrc` on macOS, if that's the shell there — same function
syntax works under zsh).

`debug.hpp` in `Templete/` is the version actually in daily use: colored output,
`pair`/`vector`/`deque`/`stack`/`queue`/`priority_queue`/`tuple`/`optional`/`variant`
support, plus `debugi()` (indexed 1D print) and `debugg()` (adjacency-list print).
`normal`'s debug include resolves its path via UltiSnips' own python
interpolation to wherever this repo is cloned, so it isn't hardcoded to one
machine.

## A note on `int`

The base template does `#define int long long` — every `int` in every template
here is actually 64-bit. Two things that follow from that, worth knowing before
you paste something into a tight memory limit: sieve/node-id arrays sized by
`N`/`MAX` are deliberately declared `int32_t`, not `int`, where the values
genuinely fit in 32 bits (an 8-byte array at `MAX` scale would be real trouble);
and `#include <ext/pb_ds/...>` (the `PBDS` snippet) has to `#undef int` before
the include and redefine it after — the macro substitution reaches into the
library's own headers otherwise and breaks them.
