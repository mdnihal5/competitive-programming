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
```cpp
ordered_set<int> s;
s.insert(5); s.insert(1); s.insert(3);
s.find_by_order(1);        // iterator to the 2nd smallest (0-indexed) -> 3
s.order_of_key(4);         // count of elements strictly < 4 -> 3
// duplicates collapse in a plain ordered_set (it's a set) -- use ordered_set<pair<int,int>>
// with a unique tiebreaker (e.g. insertion index) if you need multiset behaviour.
```
Source: `Templete/PBDS.cpp`

### `DSU` — disjoint set union, path compression + union by size
```cpp
DSU dsu(n);           // 0-indexed, n elements
dsu.unite(u, v);
dsu.connected(u, v);
dsu.compSize(u);      // size of u's component
```
Source: `Graphs/DSU.cpp`

## Graphs

### `Dijkstra` — shortest paths, non-negative weights
```cpp
Dijkstra dj(n);
dj.addEdge(u, v, w);        // directed; add both ways for an undirected edge
dj.run(src);
dj.dist[v]      // inf = unreachable, else shortest distance from src
```
Source: `Graphs/Dijkstra.cpp`

### `BellmanFord` — shortest paths, negative weights + negative-cycle detection
```cpp
BellmanFord bf(n);
bf.addEdge(u, v, w);        // directed; repeat for every edge
bf.run(src);
bf.dist[v]      // inf = unreachable, -inf = poisoned by a negative cycle, else shortest dist
bf.poisoned[v]  // explicit flag for the -inf case
```
Source: `Graphs/BellmanFord.cpp`

### `BinaryLift` — LCA, kth ancestor, distance via binary lifting
```cpp
BinaryLift bl(n);
bl.addEdge(u, v);           // repeat for every edge
bl.init();                  // or init(root) for a single tree
bl.lca(u, v); bl.dist(u, v); bl.kthAncestor(u, k);
```
Source: `Graphs/BinaryLifting.cpp`

### `WeightedLCA` — LCA + weighted path distance via binary lifting
```cpp
WeightedLCA wl(n);
wl.addEdge(u, v, w);        // repeat for every edge
wl.init(root);
wl.lca(u, v); wl.dist(u, v);   // dist = sum of edge weights on the u..v path
```
Source: `Trees/WeightedLCA.cpp`

### `SCC` — Tarjan's strongly connected components, iterative
```cpp
SCC scc(n);
scc.addEdge(u, v);          // directed; repeat for every edge
scc.run();
scc.comp[v], scc.sccCount   // component id per node, total component count
```
Source: `Graphs/SCC.cpp`

### `Bridges` — bridges + articulation points in one DFS
```cpp
BridgesArticulation ba(n);
ba.addEdge(u, v);           // undirected; repeat for every edge (parallel edges are fine)
ba.run();
ba.bridges       // vector<pair<int,int>> of bridge edges
ba.isArt[v]      // true iff v is an articulation point
```
Source: `Graphs/BridgesArticulation.cpp`

### `TopoSort` — topological sort, Kahn's algorithm
```cpp
vector<vector<int>> adj(n);   // adj[u] = list of v with edge u->v
auto order = topoSort(n, adj);
if (order.empty()) { // has a cycle }
```
Source: `Graphs/TopoSort.cpp`

### `HLD` — heavy-light decomposition for path queries
```cpp
HLD hld(n, root);
hld.addEdge(u, v);          // repeat for every tree edge
hld.build();
hld.lca(u, v);
hld.process(u, v, [&](int l, int r) { result = combine(result, segtree.query(l, r)); });
// point update at node u: segtree.update(hld.pos[u], newVal);
```
Source: `Graphs/HLD.cpp`

### `Centroid` — centroid decomposition of a tree
```cpp
CentroidDecomposition cd(n);
cd.addEdge(u, v);           // repeat for every tree edge
cd.build();
cd.centroidParent[v]        // v's parent in the centroid tree (-1 for the overall root)
// Typical use: for each query node, walk cd.centroidParent[] up to the root,
// maintaining per-centroid aggregate structures (e.g. distances) along the way.
```
Source: `Graphs/CentroidDecomposition.cpp`

### `Dinic` — max flow, Dinic's algorithm
```cpp
Dinic dn(n);
dn.addEdge(u, v, cap);      // directed; pass rcap too for an undirected edge
dn.maxflow(s, t);
```
Source: `Graphs/Dinic.cpp`

## Strings

### `ZFunction` — Z-function + pattern occurrences
```cpp
ZFunction zf(s);                             // zf.z[i] as above, zf.z[0] left 0
auto occ = ZFunction::findOccurrences(p, t);  // 0-indexed match positions of p in t
```
Source: `Strings/ZFunction.cpp`

### `KMP` — prefix-function string matching
```cpp
KMP kmp(pattern);
vector<int> occ = kmp.match(text);   // 0-indexed starting positions of pattern in text
```
Source: `Strings/KMP.cpp`

### `SuffixArray` — O(n log^2 n) suffix array + Kasai's LCP
```cpp
SuffixArray sa(s);
sa.sa[i]   // i-th suffix in sorted order (start index into s)
sa.rnk[i]  // rank of the suffix starting at i
sa.lcp[i]  // LCP between sa.sa[i] and sa.sa[i-1], for i >= 1 (min-LCP over a
// range of sa.sa via a sparse table on sa.lcp gives LCP of any two suffixes)
```
Source: `Strings/SuffixArray.cpp`

### `AhoCorasick` — multi-pattern string matching automaton
```cpp
AhoCorasick ac;
for (auto &p : patterns) ac.addPattern(p);
ac.build();
int matches = ac.countMatches(text);
```
Source: `Strings/AhoCorasick.cpp`

### `PolyHash` — anti-hash-test-safe polynomial hash, string or array
```cpp
PolyHash h(s);                // string, or PolyHash h(vec) for any numeric array
h.get(l, r);                   // hash of the [l, r] inclusive range
h.combine(leftHash, rightHash, rightLen);  // concatenate two hashes
```
Source: `Strings/PolyHash.cpp`

## Math

### `ModInt` — modular integer type with operators
```cpp
mint a = 2;
cout << power(a, 3);          // 8
assert(a * inverse(a) == 1);
// different fixed modulus: using mint2 = Modular<1'000'000'007>;
```
Source: `Maths/ModInt.cpp`

### `nCr` — nCr/nPr, auto-ready, fixed to the base template's N (existing snippet, unchanged)
```cpp
// auto-instantiated as `fac` the moment the snippet is pasted -- no construction step
fac.ncr(n, r);
fac.npr(n, r);
```

### `Comb` — nCr/nPr, custom max-N
```cpp
Combinatorics C(200000);      // size to the largest n you'll query, not MAX by habit
C.nCr(10, 3);                 // 120
```
Source: `Maths/Combinatorics.cpp`

### `CRT` — Chinese Remainder Theorem
```cpp
auto [x, L] = crt(a, m, b, n);   // x = a (mod m) and x = b (mod n), 0 <= x < L
// for k > 2 congruences fold pairwise: r = crt(a1,m1,a2,m2); r = crt(r.first,r.second,a3,m3); ...
```
Source: `Maths/CRT.cpp`

### `Totient` — Euler's totient of a single value
```cpp
int f = phi(36);   // -> 12
```
Source: `Maths/Totient.cpp`

### `FastPow` — binary exponentiation + inverse, runtime modulus
```cpp
FastPow::power(b, e, m);      // b^e mod m, any m that fits in unsigned long long
FastPow::inverse(n, m);       // n^-1 mod m, requires gcd(n, m) == 1
// fixed compile-time modulus + ergonomic operators: use ModInt.cpp's Modular<MOD> instead
```
Source: `Maths/FastPow.cpp`

### `NTT` — polynomial multiplication mod 998244353
```cpp
vector<int> c = NTT::multiply(a, b);   // a[i], b[i] already reduced mod 998244353
```
Source: `Maths/NTT.cpp`

### `Sieve` — linear sieve, primality + factorization
```cpp
Sieve sv(1000000);                 // sieve up to 1e6 -- size to what you actually need, not MAX by habit
bool p = sv.isPrime(97);           // true
vector<int32_t> f = sv.factorize(360); // {2,2,2,3,3,5}
```
Source: `Maths/primes.cpp`

## Segment trees

### `SegTree` — iterative point-update range-query, generic op
```cpp
auto st = SegTree(a, 0, [](int a, int b){ return a + b; });  // 0-indexed, identity=0 for sum
st.update(i, val);
st.query(l, r);                // [l, r] inclusive
// swap identity+lambda for min/max/gcd/xor etc -- that's the whole "modify per use case" step
```
Source: `SegmentTree/SegmentTree.cpp`

### `LazySegTree` — range-update range-query, generic op
```cpp
LazySegTree st(n);             // 1-indexed, valid range [1, n]
st.Add(l, r, v);                // range add
st.Sum(l, r); st.Min(l, r); st.Max(l, r);
```
Source: `SegmentTree/LazySegmentTree.cpp`

### `PersistentSegTree` — versioned segment tree
```cpp
auto pst = PersistentSegTree(a, 0, [](int a, int b){ return a + b; });  // version 0 = initial array
int v2 = pst.update(0, idx, val);   // creates version v2 from version 0, doesn't mutate it
pst.query(v2, l, r);            // query any version, including old ones, any time
```
Source: `SegmentTree/PersistentSegmentTree.cpp`

### `MergeSortTree` — count-less-than / order-stat range queries
```cpp
MergeSortTree mst(a);           // static -- no point-update
mst.countLess(l, r, x);         // count of a[i] < x in [l, r]
mst.predecessor(l, r, x);       // largest a[i] <= x, else INT_MIN
mst.successor(l, r, x);         // smallest a[i] >= x, else INT_MAX
```
Source: `SegmentTree/MergeSortTree.cpp`

### `MaxSubarraySeg` — max-subarray-sum segment tree
```cpp
MaxSubarraySegTree st(n, MaxSubarraySegTree::NEG_INF);  // all positions start "unset"
st.modify(pos, val);            // set position pos to val
st.query(l, r);                 // max subarray sum within [l, r]
```
Source: `SegmentTree/DynamicSubarraySum.cpp`

### `RangeToggleSum` — range XOR-toggle + range sum
```cpp
ToggleSegTree st(n);            // binary array, starts all 0
st.toggle(l, r);                // flip every bit in [l, r]
st.query(l, r);                 // count of 1s in [l, r]
```
Source: `SegmentTree/RangeToggleSum.cpp`

## Fenwick trees

### `Fenwick` — point-update range-sum + binary search
```cpp
Fenwick f(n);                   // 0-indexed, n elements
f.update(idx, val);             // add val at idx
f.query(idx);                   // prefix sum [0, idx]
f.query(l, r);                  // range sum [l, r]
f.lower_bound(val);             // smallest prefix index whose prefix sum >= val (needs non-negative updates)
```
Source: `FenwickTree/FenwickTree.cpp`

### `FenwickRUPQ` — range-update point-query BIT
```cpp
FenwickRUPQ f(n);
f.update(l, r, val);            // add val to every index in [l, r]
f.query(idx);                   // current value at idx
```
Source: `FenwickTree/FenwickRangeUpdatePointQuery.cpp`

### `FenwickRURQ` — range-update range-query BIT (two-BIT trick)
```cpp
FenwickRURQ f(n);
f.update(l, r, val);            // add val to every index in [l, r]
f.query(l, r);                  // sum over [l, r]
```
Source: `FenwickTree/FenwickRangeUpdateRangeQuery.cpp`

### `Fenwick2D` — 2D point-update rectangle-sum-query
```cpp
Fenwick2D f(n, m);
f.update(x, y, val);            // point update
f.query(x1, y1, x2, y2);        // rectangle sum, inclusive
```
Source: `FenwickTree/Fenwick2D.cpp`

## RMQ

### `SparseTable` — O(1) RMQ, generic idempotent op (min/max/gcd)
```cpp
auto st = SparseTable(a, [](int a, int b){ return min(a, b); });  // idempotent op only
st.query(l, r);                 // [l, r] inclusive
// swap the lambda for max/gcd -- NOT sum (sum isn't idempotent, would double-count overlap)
```
Source: `RMQ/SparseTable.cpp`

### `RMQ2D` — 2D range min/max query
```cpp
auto st = SparseTable2D(grid, [](int a, int b){ return min(a, b); });
st.query(x1, y1, x2, y2);       // combine over the rectangle, inclusive
```
Source: `RMQ/RMQ2D.cpp`

## DP scaffolds & optimizations

### `DigitDP` — digit-DP skeleton with worked toy example
```cpp
DigitDP dp(bound, K);
int answer = dp.count();     // # of integers in [0, bound] with digit sum <= K
// For a range [L, R]: count(R) - count(L-1), same as any prefix-counting trick.
```
Source: `DP/DigitDP.cpp`

### `BitmaskDP` — bitmask-DP skeleton with worked toy example
```cpp
BitmaskDP dp(costMatrix);      // costMatrix[worker][task]
int minCost = dp.answer();
```
Source: `DP/BitmaskDP.cpp`

### `SOSDP` — sum-over-subsets DP
```cpp
vector<int> g = sos(f);   // f.size() must be a power of two (2^n); g[mask] = sum_{sub subseteq mask} f[sub]
// For superset-sum instead of submask-sum: flip the condition to
// `if (!(mask & (1<<bit)))` and combine mask with mask|(1<<bit).
```
Source: `DP/SOSDP.cpp`

### `DnCOpt` — divide-and-conquer DP optimization
```cpp
// dp[i][j] built from dp[i-1] one layer at a time:
vector<int> prev = ..., cur(n, LLONG_MAX);
auto cost = [&](int k, int j) { return C(k, j); };   // your transition cost
solveDnC(cur, prev, 1, n, 0, n - 1, cost);            // cur[0] handled separately (base case)
```
Source: `DP/DivideAndConquerOpt.cpp`

### `KnuthOpt` — Knuth's DP optimization
```cpp
auto cost = [&](int i, int j) { return C(i, j); };   // your interval's base cost, quadrangle-inequality-satisfying
KnuthOpt opt(n, cost);
int best = opt.answer();
```
Source: `DP/KnuthOpt.cpp`

### `CHT` — convex hull trick, max/min line envelope
```cpp
LineContainer lc;
lc.add(k, m);            // insert line y = k*x + m
lc.query(x);              // max over all inserted lines at x
// for MIN: lc.add(-k, -m), then -lc.query(x)
```
Source: `DP/ConvexHullTrick.cpp`

## Misc

### `MinStack` — O(1) stack with running minimum
```cpp
MinStack ms;
ms.push(5); ms.push(2); ms.push(7);
ms.getMin();   // 2
ms.pop();      // removes 7, getMin() still 2
```
Source: `Others/MinStack.cpp`

### `PrefixSuffixMex` — prefix/suffix mex of an array
```cpp
auto [preMex, suffMex] = prefixSuffixMex(arr);
preMex[i]   // mex of arr[0..i]
suffMex[i]  // mex of arr[i..n-1]
```
Source: `Others/PrefixSuffixMex.cpp`

### `TernarySearch` — ternary search on a unimodal integer function
```cpp
int x = ternarySearchMin(lo, hi, [&](int x) { return f(x); });
int fMin = f(x);
```
Source: `Others/TernarySearch.cpp`

