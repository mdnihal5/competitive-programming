# Snippet index

Every UltiSnips trigger in `cpp.snippets`, what it gives you, and how to call it.
Open a `.cpp` file, type the trigger, hit Tab (or `<C-j>`). Keep this file updated
whenever a snippet is added, renamed, or removed — it's the lookup, `cpp.snippets`
itself carries no comments by design.

`normal` is the base template — every other snippet here is meant to be pasted
into a file that already has it (they don't redeclare `all`/`ALL`/`int`/`mod`/`N`/etc).

## Meta

### `list` — prints this whole index as a comment, mid-contest
```cpp
/*
 * Available templates -- trigger : description (INDEX.md has full usage)
 *
 * Graphs
 *   Dijkstra             shortest paths, non-negative weights
 *   ...
 */
```
Forgot a trigger name? Type `list`, hit Tab. It reads this file at expansion
time and formats every `## category` / `### \`trigger\` — description` pair as
a comment block — there's nothing to keep in sync separately, it's always
whatever this file currently says.

### Search: know roughly what you want but not the exact name

Not a snippet — a Vim completion function (`vimrc/vimrc`, `CPTemplateComplete`),
because an interactive prompt inside an UltiSnips `!p` block turned out to
re-fire on every later keystroke (tried it, broke it, removed it). **Type
your substring first**, then `<C-x><C-u>` (Vim's own "run my custom
completion") or `<C-Space>`/`Ctrl-Space` as a friendlier alias for the same
thing — insert mode only, and Ctrl-Space's terminal support varies, so
`<C-x><C-u>` is the one guaranteed to work everywhere. It matches substring,
case-insensitive, against trigger + description + category, read live from
this file. Arrow keys or `<C-n>`/`<C-p>` to browse, `<CR>` to accept — and
for 46 of the 48 triggers, that's it: the real template CODE lands at the
cursor, multi-line, correctly re-indented to match wherever you invoked it,
no Tab needed. (Vim's completion `word` field can't hold real newlines —
verified, it inserts a literal NUL byte inline instead of a line break — so
this happens via a `CompleteDone` handler doing plain `setline()`/`append()`
buffer edits, not through `word` itself.)

```
i, then:  segt<C-Space>         -> popup: SegTree / LazySegTree / PersistentSegTree
          <C-n><CR>             -> the real struct SegTree {...} code, right there
```

The exception is `list`, which uses UltiSnips' `!p` interpolation (reads
this file live) and can't be reduced to static text — picking it still just
drops the word `list` at the cursor, same as before, and needs an actual
Tab to expand. The popup's menu column says `[Tab]` for that one entry so
it's not a silent difference. `normal` never appears in this search at all
— it isn't one of this file's `### trigger` entries, just mentioned in
prose above, so it was never reachable this way to begin with. That's fine:
nobody forgets `normal`, it's the first thing typed in every file.

Type the query *before* invoking, not after: Vim computes candidates once,
at the moment you invoke, and does not re-run this function per keystroke
the way a real autocomplete widget would. Invoking with nothing typed yet
fetches everything and auto-fills the first result; typing more after that
doesn't refilter, it just falls out of the popup as literal text. Not a bug
to work around here — a real fix would mean writing a small autocomplete
engine, out of scope for a snippet library.

Deliberately not bound to `<C-i>`: in a terminal, `<C-i>` and `<Tab>` send
the identical byte (`0x09` — ASCII, true in every terminal, not a Vim
quirk), so they can't be two different keys, and `<Tab>` is UltiSnips' own
expand trigger.

## Templates & data structures

### `PBDS` — ordered_set / ordered_map (order statistics)
```
ordered_set<T>: s.find_by_order(k) -> iterator to k-th smallest (0-indexed), s.order_of_key(x) -> #elements < x.
ordered_map<K,V>: same two calls. A set collapses duplicates: for multiset use ordered_set<pair<int,int>> with a unique id.
Erase by value: s.erase(x). The #undef/#define int sandwich is required when `int` is already macro-ed to long long.
```
Source: `lib/Templete/PBDS.cpp`

### `DSU` — disjoint set union, path compression + union by size
```
DSU: 0-indexed, path compression + union by size, near O(1) per op. unite returns false if already joined.
Usage: DSU d(n); d.unite(u, v); d.connected(u, v); d.compSize(u);
```
Source: `lib/Graphs/DSU.cpp`

## Graphs

### `Dijkstra` — shortest paths, non-negative weights
```
Dijkstra: 0-indexed, directed edges (add both ways if undirected), weights must be >= 0, O((n+m) log m).
dist[v] = inf if unreachable.
Usage: Dijkstra dj(n); dj.addEdge(u, v, w); dj.run(src); dj.dist[v];
```
Source: `lib/Graphs/Dijkstra.cpp`

### `BellmanFord` — shortest paths, negative weights + negative-cycle detection
```
BellmanFord: 0-indexed, directed edges, any weights, O(n*m). dist = inf (unreachable), -inf (reachable
from a negative cycle, also flagged in poisoned[]), else the shortest distance. Use Dijkstra if w >= 0.
Usage: BellmanFord bf(n); bf.addEdge(u, v, w); bf.run(src); bf.dist[v];
```
Source: `lib/Graphs/BellmanFord.cpp`

### `BinaryLift` — LCA, kth ancestor, distance via binary lifting
```
BinaryLift: 0-indexed tree/forest, O(n log n) build, O(log n) lca/dist/kthAncestor (-1 if too far).
init() roots every component at its smallest index; init(r) roots only the tree containing r.
Usage: bl.addEdge(u, v); bl.init(); bl.lca(u, v); bl.dist(u, v); bl.kthAncestor(u, k);
```
Source: `lib/Graphs/BinaryLifting.cpp`

### `WeightedLCA` — LCA + weighted path distance via binary lifting
```
WeightedLCA wl(n); wl.addEdge(u, v, w) per edge (0-indexed, weights may be 0); wl.init(root) once.
wl.lca(u, v), wl.dist(u, v) = sum of edge weights on the path. Binary lifting: O(n log n) build, O(log n) query.
init is an iterative DFS, so 2e5-deep path trees are fine. Tree must be connected.
```
Source: `lib/Trees/WeightedLCA.cpp`

### `SCC` — Tarjan's strongly connected components, iterative
```
SCC: 0-indexed directed graph, iterative Tarjan, O(n + m). comp[v] in [0, sccCount); ids are in
reverse topological order of the condensation (edge u->v across components => comp[u] > comp[v]).
Usage: scc.addEdge(u, v); scc.run(); scc.comp[v]; scc.sccCount;
```
Source: `lib/Graphs/SCC.cpp`

### `Bridges` — bridges + articulation points in one DFS
```
BridgesArticulation: 0-indexed undirected graph, parallel edges ok, iterative DFS, O(n + m).
After run(): bridges = list of (parent, child) pairs, isArt[v] = articulation point.
Usage: ba.addEdge(u, v); ba.run();
```
Source: `lib/Graphs/BridgesArticulation.cpp`

### `TopoSort` — topological sort, Kahn's algorithm
```
topoSort: Kahn BFS, O(n + m). Returns a topological order of 0..n-1, or {} if the graph has a cycle.
Usage: vector<vector<int>> adj(n); auto order = topoSort(n, adj);
```
Source: `lib/Graphs/TopoSort.cpp`

### `HLD` — heavy-light decomposition for path queries
```
HLD: 0-indexed tree rooted at root, O(n) build, O(log n) lca, O(log n) chains per path.
pos[] is a DFS preorder: subtree of u = [pos[u], pos[u] + subSize[u] - 1]. process() gives each chain
as an inclusive pos range, NOT in u->v order (reorder inside op for non-commutative merges).
Usage: hld.addEdge(u, v); hld.build(); hld.lca(u, v); hld.process(u, v, [&](int l, int r) {...});
```
Source: `lib/Graphs/HLD.cpp`

### `Centroid` — centroid decomposition of a tree
```
CentroidDecomposition: 0-indexed connected tree, O(n log n). centroidParent[v] = parent in the centroid
tree (-1 for its root). Walk centroidParent upwards from a node to visit its O(log n) centroid ancestors.
Usage: cd.addEdge(u, v); cd.build(); cd.centroidParent[v];
```
Source: `lib/Graphs/CentroidDecomposition.cpp`

### `Dinic` — max flow, Dinic's algorithm
```
Dinic: 0-indexed max flow, O(V^2 E) worst case, recursion depth up to the s-t path length.
addEdge(u, v, cap, rcap = 0): pass rcap = cap for an undirected edge. edges[id].flow = flow on edge id.
Usage: Dinic dn(n); dn.addEdge(u, v, c); int f = dn.maxflow(s, t);
```
Source: `lib/Graphs/Dinic.cpp`

## Strings

### `ZFunction` — Z-function + pattern occurrences
```
ZFunction zf(s): zf.z[i] = LCP(s, s[i..]), z[0] = 0.
ZFunction::findOccurrences(p, t) -> 0-indexed starts of p in t (assumes char \1 absent from input). O(|p| + |t|).
```
Source: `lib/Strings/ZFunction.cpp`

### `KMP` — prefix-function string matching
```
KMP kmp(pattern) (pattern non-empty); kmp.pi = prefix function.
kmp.match(text) -> 0-indexed start positions of every (overlapping) occurrence. O(|pat| + |text|).
```
Source: `lib/Strings/KMP.cpp`

### `SuffixArray` — O(n log n) suffix array + Kasai's LCP
```
SuffixArray s(str): sa[i] = start of i-th smallest suffix, rnk = inverse of sa,
lcp[i] = LCP(suffix sa[i], suffix sa[i-1]), lcp[0] = 0. Works for any bytes, any |s| >= 0.
O(n log n) prefix doubling with counting sort + Kasai. LCP of arbitrary suffixes = range-min of lcp (SparseTable).
```
Source: `lib/Strings/SuffixArray.cpp`

### `AhoCorasick` — multi-pattern string matching automaton
```
AhoCorasick ac; ac.addPattern(p) for each pattern; ac.build() ONCE after all adds.
ac.countMatches(text) = total (overlapping, duplicates-counted) occurrences of all patterns.
Alphabet is ALPHA/BASE (default a-z); change both constants for another alphabet. O(total + |text|*1).
```
Source: `lib/Strings/AhoCorasick.cpp`

### `PolyHash` — anti-hash-test-safe polynomial hash, string or array
```
PolyHash h(string) or h(vector<T>) (any integer T, negatives ok); 0-indexed.
h.get(l, r) inclusive substring hash mod 2^61-1 with a random base per run; h.combine(hashL, hashR, lenR) = hash of concat.
O(n) build, O(1) get. Every element maps to [1, MOD-1], so [-1, 5] never collides with [5] (old code mapped -1 to 0).
```
Source: `lib/Strings/PolyHash.cpp`

### `Trie` — array trie: insert/erase, count words and prefixes
```
Trie t (lowercase a-z; change ALPHA/BASE for another alphabet): insert(s) (multiset: duplicates counted),
search(s) exact word, startsWith(prefix), remove(s) -> false if absent (removes one copy).
O(|s|) each. Nodes are never freed (counters keep it correct), so memory = total inserted length * 26 * 8 bytes.
```
Source: `lib/Others/WordTrie.cpp`

## Math

### `ModInt` — modular integer type with operators
```
Modular<MOD>: MOD must be prime (division uses Fermat), +,-,*,/ , power(a, e >= 0), inverse(a), cin/cout.
Usage: mint a = 2; cout << power(a, 3) << a / 5; using mint2 = Modular<1000000007>;
```
Source: `lib/Maths/ModInt.cpp`

### `Comb` — nCr/nPr, custom max-N (see also existing nCr)
```
Combinatorics: factorial tables mod `mod` (must be a prime > maxN), O(maxN) build, O(1) nCr/nPr.
Indices a must be <= maxN; out-of-range b gives 0.
Usage: Combinatorics C(maxN); C.nCr(a, b); C.nPr(a, b);
```
Source: `lib/Maths/Combinatorics.cpp`

### `nCr` — nCr/nPr, auto-ready, fixed to the base template's N (existing snippet, unchanged)
```cpp
// auto-instantiated as `fac` the moment the snippet is pasted -- no construction step
fac.ncr(n, r);
fac.npr(n, r);
```

### `CRT` — Chinese Remainder Theorem
```
crt(a, m, b, n): x = a (mod m), x = b (mod n), moduli need not be coprime; returns {x, lcm}, 0 <= x < lcm.
Asserts when the system is inconsistent; lcm and m*n/g must fit in 64 bits. Fold pairwise for k > 2.
Usage: auto [x, L] = crt(a, m, b, n);
```
Source: `lib/Maths/CRT.cpp`

### `Totient` — Euler's totient of a single value
```
phi(n): Euler totient by trial division, O(sqrt n). phi(1) = 1.
Usage: int f = phi(n);
```
Source: `lib/Maths/Totient.cpp`

### `FastPow` — binary exponentiation + inverse, runtime modulus
```
FastPow: unsigned 64-bit modpow/mulmod via __uint128_t (any m < 2^63), O(log e).
inverse(n, m) works for any m (not just prime) as long as gcd(n, m) == 1. For operator syntax use ModInt.
Usage: FastPow::power(b, e, m); FastPow::inverse(n, m);
```
Source: `lib/Maths/FastPow.cpp`

### `NTT` — polynomial multiplication mod 998244353
```
NTT::multiply(a, b): convolution mod 998244353, O(n log n). Inputs must be reduced into [0, MOD);
result size |a| + |b| - 1 (<= 2^23). Empty input gives empty output.
Usage: vector<int> c = NTT::multiply(a, b);
```
Source: `lib/Maths/NTT.cpp`

### `Sieve` — linear sieve, primality + factorization
```
Sieve: linear sieve up to n, O(n). spf = smallest prime factor, primes ascending. isPrime/factorize need
x <= n; factorize is O(log x) with multiplicity. Stored as int32 on purpose (memory for n ~ 1e7).
Usage: Sieve sv(n); sv.isPrime(x); sv.factorize(x); sv.primes;
```
Source: `lib/Maths/primes.cpp`

## Segment trees

### `SegTree` — iterative point-update range-query, generic op
```
SegTree<T,F> st(a, identity, combine): 0-indexed, query(l, r) inclusive, update(i, v) = point assign.
combine must be associative; commutativity NOT required (order is preserved).
Build O(n), update/query O(log n). Iterative bottom-up, any n >= 1.
```
Source: `lib/SegmentTree/SegmentTree.cpp`

### `LazySegTree` — range-update range-query, generic op
```
LazySegTree st(n): 1-indexed [1, n], all zeros initially.
Add(l, r, v) range add; Min/Max/Sum(l, r) range queries. All O(log n).
Needs inf (1e18) from the prelude as the min/max identity.
```
Source: `lib/SegmentTree/LazySegmentTree.cpp`

### `PersistentSegTree` — versioned segment tree
```
PersistentSegTree st(a, identity, combine): version 0 = a. 0-indexed.
v2 = st.update(v, i, val) -> new version id (old versions stay valid); st.query(v, l, r) inclusive.
Each update adds O(log n) nodes (total nodes <= 2n + updates*(log n + 1)); query O(log n).
```
Source: `lib/SegmentTree/PersistentSegmentTree.cpp`

### `MergeSortTree` — count-less-than / order-stat range queries
```
MergeSortTree t(a): static array, 0-indexed, queries on [l, r] inclusive (no updates).
countLess(l, r, x) = #a[i] < x; predecessor = largest a[i] <= x else -inf; successor = smallest a[i] >= x else inf.
Build O(n log n) time+memory, query O(log^2 n). Values must satisfy |a[i]| < inf.
```
Source: `lib/SegmentTree/MergeSortTree.cpp`

### `MaxSubarraySeg` — max-subarray-sum segment tree
```
MaxSubarraySegTree st(a): 0-indexed, update(i, v) = point assign, query(l, r) = max NON-EMPTY subarray sum in [l, r].
Values may be negative; |sum| should stay well below 1e18 (identity uses -inf).
Build O(n), update/query O(log n). Iterative, any n >= 1.
```
Source: `lib/SegmentTree/DynamicSubarraySum.cpp`

### `RangeToggleSum` — range XOR-toggle + range sum
```
ToggleSegTree st(n): 0-indexed binary array, all 0 initially.
toggle(l, r) flips every bit in [l, r]; query(l, r) = number of ones in [l, r]. Both O(log n).
```
Source: `lib/SegmentTree/RangeToggleSum.cpp`

## Fenwick trees

### `Fenwick` — point-update range-sum + binary search
```
Fenwick: 0-indexed point add, prefix/range sum, O(log n). lower_bound(v) = first index whose prefix
sum >= v (n if none); only valid while all stored values are >= 0.
Usage: f.update(i, v); f.query(l, r); f.lower_bound(v);
```
Source: `lib/FenwickTree/FenwickTree.cpp`

### `FenwickRUPQ` — range-update point-query BIT
```
FenwickRUPQ: 0-indexed inclusive range add, point read, O(log n).
Usage: f.update(l, r, v); f.query(i);
```
Source: `lib/FenwickTree/FenwickRangeUpdatePointQuery.cpp`

### `FenwickRURQ` — range-update range-query BIT (two-BIT trick)
```
FenwickRURQ: 0-indexed inclusive range add + range sum (two BITs), O(log n).
Usage: f.update(l, r, v); f.query(l, r);
```
Source: `lib/FenwickTree/FenwickRangeUpdateRangeQuery.cpp`

### `Fenwick2D` — 2D point-update rectangle-sum-query
```
Fenwick2D: 0-indexed point update, rectangle sum (inclusive corners), O(log n * log m).
Usage: f.update(x, y, v); f.query(x1, y1, x2, y2);
```
Source: `lib/FenwickTree/Fenwick2D.cpp`

## RMQ

### `SparseTable` — O(1) RMQ, generic idempotent op (min/max/gcd)
```
SparseTable<T,F> st(a, combine): 0-indexed, query(l, r) inclusive.
combine must be associative AND idempotent (min/max/gcd/and/or), NOT sum.
Build O(n log n) memory/time, query O(1).
```
Source: `lib/RMQ/SparseTable.cpp`

### `RMQ2D` — 2D range min/max query
```
SparseTable2D<T,F> st(grid, combine): 0-indexed, query(x1, y1, x2, y2) inclusive corners.
combine must be associative + idempotent (min/max/gcd). Grid must be non-empty.
Build O(nm log n log m) time and memory, query O(1).
```
Source: `lib/RMQ/RMQ2D.cpp`

## DP scaffolds & optimizations

### `DigitDP` — digit-DP skeleton with worked toy example
```
DigitDP: count integers in [0, bound] with digit sum <= K; state (pos, sum), non-tight memoised.
Add problem state to solve()/memo and the end test at pos == size. Range [L,R]: count(R) - count(L-1)
(negative bound is not supported, guard L=0).
Usage: DigitDP dp(bound, K); int ans = dp.count();
```
Source: `lib/DP/DigitDP.cpp`

### `BitmaskDP` — bitmask-DP skeleton with worked toy example
```
BitmaskDP: assignment problem, cost[worker][task] (square), O(2^n * n). Edit solve() for other
bitmask problems (worker = popcount(mask) trick).
Usage: BitmaskDP dp(cost); int best = dp.answer();
```
Source: `lib/DP/BitmaskDP.cpp`

### `SOSDP` — sum-over-subsets DP
```
sos(f): g[mask] = sum of f[sub] over submasks sub of mask; f.size() must be a power of two. O(n * 2^n).
Superset sum: test (mask & b) == 0 and add f[mask | b]. Other ops (max, xor): change the +=.
Usage: vector<int> g = sos(f);
```
Source: `lib/DP/SOSDP.cpp`

### `DnCOpt` — divide-and-conquer DP optimization
```
solveDnC: one layer of dp[j] = min_{k<j}(prev[k] + cost(k, j)) when opt(j) is monotone in j
(quadrangle inequality). O(n log n) per layer. 0-indexed, fills cur[lo..hi).
Usage: solveDnC(cur, prev, 1, n, 0, n - 1, cost); cur[0] is the base case, handle it yourself.
```
Source: `lib/DP/DivideAndConquerOpt.cpp`

### `KnuthOpt` — Knuth's DP optimization
```
KnuthOpt: dp[i][j] = min_{i<=k<j}(dp[i][k] + dp[k+1][j]) + cost(i, j), 0-indexed, O(n^2) memory+time.
Needs cost to satisfy the quadrangle inequality (opt[i][j-1] <= opt[i][j] <= opt[i+1][j]).
Usage: KnuthOpt opt(n, [&](int i, int j) { return ...; }); int best = opt.answer();
```
Source: `lib/DP/KnuthOpt.cpp`

### `CHT` — convex hull trick, max/min line envelope
```
LineContainer (KACTL): max of lines k*x+m at x; amortised O(log n) add/query. Needs lines >= 1
(query on empty set is UB). For MIN: add(-k, -m), answer is -query(x).
Usage: lc.add(k, m); lc.query(x);
```
Source: `lib/DP/ConvexHullTrick.cpp`

## Misc

### `MinStack` — O(1) stack with running minimum
```
MinStack ms: push(x), pop(), top(), getMin() (min of whole stack), size(), empty(). All O(1).
pop/top/getMin on an empty stack is undefined (check empty() first).
```
Source: `lib/Others/MinStack.cpp`

### `MinDeque` — O(1) queue with running minimum (sliding window)
```
MinDeque d (self-contained, two stacks): push_front/push_back(x), pop_front/pop_back(), front(), back(),
getMin() (min of whole deque), size(), empty(). Amortised O(1) (a one-sided drain splits the stack in half).
Does not clash with Others/MinStack.cpp. Calls on an empty deque are undefined.
```
Source: `lib/Others/MinStack_Mindeque.cpp`

### `PrefixSuffixMex` — prefix/suffix mex of an array
```
auto [pre, suf] = prefixSuffixMex(a): pre[i] = mex(a[0..i]), suf[i] = mex(a[i..n-1]).
Negative or > n values are ignored (cannot affect the mex). O(n) time and memory.
```
Source: `lib/Others/PrefixSuffixMex.cpp`

### `TernarySearch` — ternary search on a unimodal integer function
```
ternarySearchMin(lo, hi, f): integer x in [lo, hi] minimising f; f strictly decreasing then strictly increasing
(a flat run is allowed only at the minimum). For a maximum pass [&](int x){ return -f(x); }.
Implemented as a binary search on the slope f(m) <= f(m+1): ~2*log2(range) evaluations, no plateau traps.
```
Source: `lib/Others/TernarySearch.cpp`

### `BalMultiset` — multiset with lower median and sum of |v - median|
```
BalancedMultiset s: insert(x), erase(x) (x must be present), size(), median() = LOWER median (sorted[(size-1)/2]),
query() = sum |v - median| over all elements (the min total cost to make all equal). Sliding-window median/cost.
All O(log n); median()/query() need a non-empty set.
```
Source: `lib/Others/BalancedMultiset.cpp`

### `DivWindow` — n/k minus max block frequency over divisor windows
```
minimumOperationsToMakeKPeriodic(word, k)  (LeetCode 3137; k divides |word|): one operation copies a k-block
over another k-block. Answer = (#blocks) - (frequency of the most common k-block). O(|word|).
```
Source: `lib/Others/divisor_window.cpp`
