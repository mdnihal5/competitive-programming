# C++ Snippets Collection

This repository contains a collection of C++ code snippets organized by category. These snippets are designed to streamline your coding workflow by providing quick access to common patterns and utilities in competitive programming and system development.

## Categories

### General Snippets

- **normal**: A comprehensive template for competitive programming with PBDS, debugging macros, and optimizations.
- **simple**: A basic template with essential includes and debugging macros.
- **c++**: A minimal C++ template for quick setup in coding competitions.

### Data Structures

- **segtree**: A basic Segment Tree class with support for range queries and point updates.
- **lazysegtree**: A Lazy Segment Tree class for efficient range updates and queries.
- **FenwickTree**: A Fenwick Tree (Binary Indexed Tree) implementation for prefix sum queries.

### Math Operations

- **binpower**: A function for fast exponentiation (binary exponentiation).
- **inverse**: A function to compute the modular inverse using the extended Euclidean algorithm.
- **primes**: Sieve of Eratosthenes and prime factorization functions.

### Graph Algorithms

- **dijkstra**: Dijkstra's algorithm for finding the shortest path in a graph.
- **DSU**: Disjoint Set Union (Union-Find) data structure for efficient union and find operations.
- **Graph**: A basic graph template for graph-related algorithms.

### Advanced Algorithms

- **Zalgo**: Z-Algorithm for string matching.
- **StringHash**: A template for string hashing using rolling hash.

### Miscellaneous

- **orderedset**: Snippets for working with ordered sets and maps using PBDS.
- **combinations**: Function for computing combinations (nCr) using modular arithmetic.

## Usage

Simply copy the desired snippet into your code editor, and start coding! Each snippet is designed to be self-contained and easy to integrate into larger projects.


```
/*
   1. normal -> templete
   2. simple -> simple templete
   3. c++ -> basic c++ templete
   4. segtree -> segtree
   5. lazysegtree -> lazysegtree
   6. primes ->"prime operations
   7. binpower -> binexpo
   8. inverse -> modinverse
   9. orderedset -> pbds
   10. combinations -> nCr
   11. dijkstra -> dijkstra
   12. DSU -> UnionFind
   13. Graph -> Graph
   14. Zalgo -> Z algorithm
   15. StringHash -> string hashing
   16. FenwickTree ->  FenwickTree
   17. ModInt -> modular int
 */
```

```cpp
// Author : md_nihal

#include "bits/stdc++.h"
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2,fma")
#define Md_Nihal ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef unsigned long long ull;
#define endl "\n"
#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define vpi vector<pii>
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
using i_64 = int64_t;
using u_64 = uint64_t;
using u_128 = __uint128_t;
const int mod = 1E9 + 7, inf = 1E18, N = 2e5 + 7, MAX = 2e7 + 7;

template<class T, class V>istream &operator>> (istream &in, pair<T, V> &a) {in >> a.first >> a.second; return in;}
template<class T>istream &operator>> (istream &in, vector<T> &a) {for (auto &i : a) {in >> i;} return in;}
template<class T, class V>ostream &operator<< (ostream &os, pair<T, V> &a) {os << a.first << " " << a.second; return os;}
template<class T>ostream &operator<< (ostream &os, vector<T> &a) {for (auto &i : a) {os << i << " ";} return os;}

/*----------------------------------------------- PBDS --------------------------------------------*/

using namespace __gnu_pbds;
template<typename T, typename Compare = std::greater<T>>
using heap = std::priority_queue<T, std::vector<T>, Compare>;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
template<class key, class value, class cmp = less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;

/*----------------------------------------------- PBDS ends --------------------------------------------*/

#ifndef ONLINE_JUDGE
    #include "/home/anonymous/Templates/debug.hpp"
#else
    #define debug(x...);
#endif

/*=========================================== SOLUTION ===========================================*/

void ____solve() {

    $0

}

/*============================================= MAIN =============================================*/

int32_t  main() {
    Md_Nihal;
    int Testcases = 1;    $1cin >> Testcases;

    for (int i = 0; i < Testcases; i++, ____solve(), cout << endl);
}
```

```cpp
#include "bits/stdc++.h"
using namespace std;

#define endl "\n"
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
using i_64 = int64_t;
const int mod = 1E9 + 7, inf = 1E18, N = 2e5 + 7, MAX = 2e7 + 7;

#ifndef ONLINE_JUDGE
    #include "/home/anonymous/Templates/debug.hpp"
#else
    #define debug(x...);
#endif

/*=========================================== SOLUTION ===========================================*/

void ____solve() {

    $0

}

/*============================================= MAIN =============================================*/

int32_t main() {
    int Test = 1;  $1cin >> Test;

    for (int i = 0; i < Test; i++, ____solve(), cout << endl);
}

```
```cpp
#include<bits/stdc++.h>
using namespace std;
void __solve() {

    $0
}

int main() {
    int T = 1; $1cin >> T;

    while (T--) __solve();
}
```
```cpp
template<typename T>
class SegmentTree {
  private:
    vector<T> tree;
    vector<T> nums;
    int n;
    T identity;

    bool isValid (int idx) {
        return idx >= 0 && idx < n;
    }

    T combine (T left, T right) {
        return left + right;
    }

    void build (int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];

        } else {
            int mid = start + (end - start) / 2;
            build (2 * node, start, mid);
            build (2 * node + 1, mid + 1, end);
            tree[node] = combine (tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update (int node, int start, int end, int idx) {
        if (start == end) {
            tree[node] = nums[start];

        } else {
            int mid = start + (end - start) / 2;

            if (start <= idx && idx <= mid) {
                update (2 * node, start, mid, idx);

            } else {
                update (2 * node + 1, mid + 1, end, idx);
            }

            tree[node] = combine (tree[2 * node], tree[2 * node + 1]);
        }
    }

    T query (int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return identity;
        }

        if (l <= start && end <= r) {
            return tree[node];
        }

        int mid = start + (end - start) / 2;
        T leftResult = query (2 * node, start, mid, l, r);
        T rightResult = query (2 * node + 1, mid + 1, end, l, r);
        return combine (leftResult, rightResult);
    }

  public:
    SegmentTree (const vector<T> &nums, T identity) : nums (nums), identity (identity) {
        n = nums.size();
        tree.resize (4 * n, identity);
        build (1, 0, n - 1);
    }
    SegmentTree (int size, T identity) : identity (identity) {
        n = size;
        nums.resize (n, identity);
        tree.resize (4 * n, identity);
        build (1, 0, n - 1);
    }
    void update (int idx, T val) {
        nums[idx] = val;
        update (1, 0, n - 1, idx);
    }

    T query (int l, int r) {
        return query (1, 0, n - 1, l, r);
    }
};

template<typename T>
class LazySegmentTree {
  private:
    vector<T> tree, lazy;
    vector<T> nums;
    int n;
    T identity;

    bool isValid (int idx) {
        return idx >= 0 && idx < n;
    }

    T combine (T left, T right) {
        return left + right; // Change this for different operations
    }

    void apply (T &a, T b, int length) {
        a += b * length; // Change this for different operations
    }

    void build (int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];

        } else {
            int mid = start + (end - start) / 2;
            build (2 * node, start, mid);
            build (2 * node + 1, mid + 1, end);
            tree[node] = combine (tree[2 * node], tree[2 * node + 1]);
        }
    }

    void push (int node, int start, int end) {
        if (lazy[node] != identity) {
            apply (tree[node], lazy[node], end - start + 1);

            if (start != end) {
                lazy[2 * node] = combine (lazy[2 * node], lazy[node]);
                lazy[2 * node + 1] = combine (lazy[2 * node + 1], lazy[node]);
            }

            lazy[node] = identity;
        }
    }

    void updateRange (int node, int start, int end, int l, int r, T val) {
        push (node, start, end);

        if (r < start || end < l) {
            return;
        }

        if (l <= start && end <= r) {
            lazy[node] = combine (lazy[node], val);
            push (node, start, end);
            return;
        }

        int mid = start + (end - start) / 2;
        updateRange (2 * node, start, mid, l, r, val);
        updateRange (2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = combine (tree[2 * node], tree[2 * node + 1]);
    }

    T queryRange (int node, int start, int end, int l, int r) {
        push (node, start, end);

        if (r < start || end < l) {
            return identity;
        }

        if (l <= start && end <= r) {
            return tree[node];
        }

        int mid = start + (end - start) / 2;
        T leftResult = queryRange (2 * node, start, mid, l, r);
        T rightResult = queryRange (2 * node + 1, mid + 1, end, l, r);
        return combine (leftResult, rightResult);
    }

  public:
    LazySegmentTree (const vector<T> &nums, T identity) : nums (nums), identity (identity) {
        n = nums.size();
        tree.resize (4 * n, identity);
        lazy.resize (4 * n, identity);
        build (1, 0, n - 1);
    }

    LazySegmentTree (int size, T identity) : identity (identity) {
        n = size;
        nums.resize (n, identity);
        tree.resize (4 * n, identity);
        lazy.resize (4 * n, identity);
        build (1, 0, n - 1);
    }

    void updateRange (int l, int r, T val) {
        updateRange (1, 0, n - 1, l, r, val);
    }

    T queryRange (int l, int r) {
        return queryRange (1, 0, n - 1, l, r);
    }
};
```
```cpp
bool marked[N];
int  sp[N];

void Sieve() {
    for (int i = 2; i < N; i += 2)  sp[i] = 2;//even numbers have smallest prime factor 2

    for (int i = 3; i < N; i += 2) {
        if (!marked[i]) {
            sp[i] = i;

            for (int j = i; (j * i) < N; j += 2) {
                if (!marked[j * i]) marked[j * i] = true, sp[j * i] = i;
            }
        }
    }
}


vector <int> factorize (int k) {
    vector <int> ans;

    while (k > 1) {
        ans.push_back (sp[k]);
        k /= sp[k];
    }

    return ans;
}
```
```cpp
template<typename T>
T binpow (T a, T b) {
    T ans = 1;

    while (b) {
        if (b & 1) {
            ans = 1LL * ans * a % mod;
        }

        a = 1LL * a * a % mod;
        b >>= 1;
    }

    return ans;
}
```
```cpp
ll inv (ll a, ll m) {
    if (a == 1) {
        return 1;
    }

    return (1LL - inv (m % a, a) * m) / a + m;
}
```
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
template<class key, class value, class cmp = less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;
```
```cpp
class FenwickTree {
    vector<int>tree;
    int size;
  public:
    FenwickTree (int n) : tree (n + 1, 0), size (n) {};
    void update (int idx, int add) {
        for (++idx; idx <= size; idx += idx & -idx) {
            tree[idx] += add;
        }
    }
    int query (int idx) {
        int sum = 0;

        for (++idx; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }

        return sum;
    }
    int sum (int l, int r) {
        return query (r) - query (l - 1);
    }
    int lower_bound (int val) {
        int ind = 0, sum = 0;

        for (int i = 20; i >= 0; i--) {
            if ( ind + (1 << i) <= size && tree[ind + (1 << i)] + sum < val) {
                ind += (1 << i);
                sum += tree[ind];
            }
        }

        return ind + 1;
    }
};
```
```cpp
int fact[N];
int exp (int a, int b) {
    int ans = 1;
    a %= mod;

    while (b) {
        if (b & 1) ans = (ans * 1ll * a) % mod;

        b >>= 1;
        a = (a * 1ll * a) % mod;
    }

    return ans;
}
int nCr (int a, int b) {
    if (b > a) return 0;

    return fact[a] * 1ll * exp (fact[b] * 1ll * fact[a - b] % mod, mod - 2) % mod;
}
```
```cpp
vector<int>dikstra (vector<vector<pii>> &graph, int source, int n) {
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    vector<int>dist (n, inf);
    dist[source] = 0;
    pq.push ({0, source});

    while (!pq.empty() ) {
        auto [currDistance, node] = pq.top();
        pq.pop();

        if (currDistance != dist[node]) continue;

        for (auto [neighbour, weight] : graph[node]) {
            if (dist[neighbour] > dist[node] + weight) {
                dist[neighbour] = dist[node] + weight; pq.push ({dist[neighbour], neighbour});
            }
        }
    }

    return dist;
}
```
```cpp
class DSU {
    std::vector<int>par, size;
  public:
    DSU (int n) : par (n + 5), size (n + 5) {
        for (int i = 0; i <= n; i++) size[i] = 1, par[i] = i;
    }
    int parent (int x) {
        return (par[x] == x ? x : parent (par[x]) );
    }
    void unite (int x, int y) {
        int rootx = parent (x), rooty = parent (y);

        if (rootx == rooty) return;

        if (size[rootx] < size[rooty]) swap (rootx, rooty);

        par[rooty] = rootx;
        size[rootx] += size[rooty];
    }
    bool connected (int x, int y) {
        return parent (x) == parent (y);
    }
    int get_size (int x) {
        return size[parent (x)];
    }
};
```
```cpp
class Zalgo {
  private:
    string text;
    string pattern;
    vector<int> Z;
    vector<int> calculateZ (const string &s) {
        int n = s.length();
        vector<int> Z (n, 0);
        int l = 0, r = 0;

        for (int i = 1; i < n; ++i) {
            if (i <= r)
                Z[i] = min (r - i + 1, Z[i - l]);

            while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
                ++Z[i];

            if (i + Z[i] - 1 > r) {
                l = i;
                r = i + Z[i] - 1;
            }
        }

        return Z;
    }
  public:
    ZAlgorithm (const string &txt, const string &pat) : text (txt), pattern (pat) {
        string combined = pattern + "$" + text;
        Z = calculateZ (combined);
    }
    vector<int> findOccurrences() {
        int patternLength = pattern.length();
        vector<int> occurrences;

        for (int i = patternLength + 1; i < Z.size(); ++i) {
            if (Z[i] == patternLength)
                occurrences.push_back (i - patternLength - 1);
        }

        return occurrences;
    }
};
```
```cpp
#define MAXLEN 1000010
constexpr uint64_t prime = (1ULL << 61) - 1;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64 (seed) () % (prime / 3) + (prime / 3);
uint64_t base_pow[MAXLEN];
int64_t primemul (uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & prime) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & prime) + (ret >> 61);
    ret = (ret & prime) + (ret >> 61);
    return ret - 1;
}
void init() {
    base_pow[0] = 1;

    for (int i = 1; i < MAXLEN; i++) {
        base_pow[i] = primemul (base_pow[i - 1], base);
    }
}
struct PolyHash {
    /// Remove suff vector and usage if reverse hash is not required for more speed
    vector<int64_t> pref, suff;

    PolyHash() {}

    template <typename T>
    PolyHash (const vector<T> &ar) {
        if (!base_pow[0]) init();

        int n = ar.size();
        assert (n < MAXLEN);
        pref.resize (n + 3, 0), suff.resize (n + 3, 0);

        for (int i = 1; i <= n; i++) {
            pref[i] = primemul (pref[i - 1], base) + ar[i - 1] + 997;

            if (pref[i] >= prime) pref[i] -= prime;
        }

        for (int i = n; i >= 1; i--) {
            suff[i] = primemul (suff[i + 1], base) + ar[i - 1] + 997;

            if (suff[i] >= prime) suff[i] -= prime;
        }
    }
    PolyHash (const string &str)
        : PolyHash (vector<char> (str.begin(), str.end() ) ) {}

    uint64_t hash (int l, int r) {
        int64_t h = pref[r + 1] - primemul (base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + prime : h;
    }

    uint64_t rhash (int l, int r) {
        int64_t h = suff[l + 1] - primemul (base_pow[r - l + 1], suff[r + 2]);
        return h < 0 ? h + prime : h;
    }
    uint64_t combine (uint64_t hash1, uint64_t hash2, int len2) {
        return (primemul (hash1, base_pow[len2]) + hash2) % prime;
    }

};
```
```cpp

template<typename T>
struct RMQ {
    vector<vector<T>> spt;

    RMQ (const vector<T> &a) : spt (1, a) {
        int n = (int) a.size();

        for (int j = 1; 1 << j <= n; j++) {
            spt.emplace_back (n - (1 << j) + 1);

            for (int i = 0; i + (1 << j) <= n; i++)
                spt[j][i] = min (spt[j - 1][i], spt[j - 1][i + (1 << (j - 1) )]);
        }
    }

    T query (int i, int j) {
        int k = __lg (j - i + 1);
        return min (spt[k][i], spt[k][j - (1 << k) + 1]);
    }
};

```
```cpp
struct LCA {
    int n;
    vector<int> in, out, depth, path, ret;
    vector<vector<int>> adj;
    RMQ<int> rmq;

    LCA (int _n) : n (_n), in (n, -1), out (n), depth (n), adj (n), rmq ({}) {}

    void addEdge (int u, int v) {
        adj[u].push_back (v);
        adj[v].push_back (u);
    }

    void init (int r = -1) {
        if (r == -1) {
            for (int u = 0; u < n; u++)
                if (in[u] == -1)
                    dfs (u, -1);

        } else {
            dfs (r, -1);
        }

        rmq = RMQ<int> (ret);
    }

    void dfs (int u, int p) {
        in[u] = (int) path.size();
        path.push_back (u);
        ret.push_back (in[u]);

        for (int v : adj[u])
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs (v, u);
                path.push_back (u);
                ret.push_back (in[u]);
            }

        out[u] = (int) path.size();
    }

    int lca (int u, int v) {
        if (in[u] > in[v])
            swap (u, v);

        return path[rmq.query (in[u], in[v])];
    }

    int dist (int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca (u, v)];
    }

    bool anc (int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }
};
```
```cpp
struct BinaryLift {
    int n, lg;
    vector<int> depth;
    vector<vector<int>> adj, up;

    BinaryLift (int _n) : n (_n), lg (__lg (n - 1) + 1), depth (n), adj (n), up (lg, vector<int> (n, -1) ) {}

    void addEdge (int u, int v) {
        adj[u].push_back (v);
        adj[v].push_back (u);
    }

    void init (int r = -1) {
        if (r == -1) {
            for (int u = 0; u < n; u++)
                if (up[0][u] == -1)
                    dfs (u);

        } else {
            dfs (r);
        }

        for (int i = 1; i < lg; i++)
            for (int j = 0; j < n; j++)
                if (up[i - 1][j] != -1)
                    up[i][j] = up[i - 1][up[i - 1][j]];
    }

    void dfs (int u) {
        for (int v : adj[u])
            if (v != up[0][u]) {
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                dfs (v);
            }
    }

    int lca (int u, int v) {
        if (depth[u] < depth[v])
            swap (u, v);

        for (int i = lg - 1; i >= 0; i--)
            if (depth[u] - (1 << i) >= depth[v])
                u = up[i][u];

        if (u == v)
            return u;

        for (int i = lg - 1; i >= 0; i--)
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }

        return up[0][u];
    }

    int dist (int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca (u, v)];
    }

    int kthAnc (int u, int k) {
        if (k > depth[u])
            return -1;

        for (int i = 0; i < lg; i++)
            if (k >> i & 1)
                u = up[i][u];

        return u;
    }
};
```
```cpp
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

template<typename T>
constexpr T power (T a, u64 b) {
    T res {1};

    for (; b != 0; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }

    return res;
}

template<u32 P>
constexpr u32 mulMod (u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template<u64 P>
constexpr u64 mulMod (u64 a, u64 b) {
    u64 res = a * b - u64 (1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<typename U, U P>
requires std::unsigned_integral<U>
struct ModIntBase {
  public:
    constexpr ModIntBase() : x {0} {}

    template<typename T>
    requires std::integral<T>
    constexpr ModIntBase (T x_) : x {norm (x_ % T {P}) } {}

    constexpr static U norm (U x) {
        if ( (x >> (8 * sizeof (U) - 1) & 1) == 1) {
            x += P;
        }

        if (x >= P) {
            x -= P;
        }

        return x;
    }

    constexpr U val() const {
        return x;
    }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = norm (P - x);
        return res;
    }

    constexpr ModIntBase inv() const {
        return power (*this, P - 2);
    }

    constexpr ModIntBase &operator*= (const ModIntBase &rhs) & {
        x = mulMod<P> (x, rhs.val() );
        return *this;
    }

    constexpr ModIntBase &operator+= (const ModIntBase &rhs) & {
        x = norm (x + rhs.x);
        return *this;
    }

    constexpr ModIntBase &operator-= (const ModIntBase &rhs) & {
        x = norm (x - rhs.x);
        return *this;
    }

    constexpr ModIntBase &operator/= (const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator* (ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator+ (ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator- (ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator/ (ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::ostream &operator<< (std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }

    friend constexpr bool operator== (ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!= (ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }

    friend constexpr bool operator< (ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
    }

  private:
    U x;
};
```
```cpp
template<u32 P>
using ModInt = ModIntBase<u32, P>;

template<u64 P>
using ModInt64 = ModIntBase<u64, P>;

constexpr u32 P = 1000000007;
using Mint = ModInt<P>;

struct Comb {
    int n;
    std::vector<Mint> _fac;
    std::vector<Mint> _invfac;
    std::vector<Mint> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb (int n) : Comb() {
        init (n);
    }

    void init (int m) {
        if (m <= n) return;

        _fac.resize (m + 1);
        _invfac.resize (m + 1);
        _inv.resize (m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }

        _invfac[m] = _fac[m].inv();

        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }

        n = m;
    }

    Mint fac (int m) {
        if (m > n) init (2 * m);

        return _fac[m];
    }
    Mint invfac (int m) {
        if (m > n) init (2 * m);

        return _invfac[m];
    }
    Mint inv (int m) {
        if (m > n) init (2 * m);

        return _inv[m];
    }
    Mint binom (int n, int m) {
        if (n < m || m < 0) return 0;

        return fac (n) * invfac (m) * invfac (n - m);
    }
} comb;


template<int MOD = 1000000007>
struct ModInt {
    long long v;
    ModInt (long long _v = 0) {v = (-MOD < _v && _v < MOD) ? _v : _v % MOD; if (v < 0) v += MOD;}
    ModInt &operator += (const ModInt &other) {v += other.v; if (v >= MOD) v -= MOD; return *this;}
    ModInt &operator -= (const ModInt &other) {v -= other.v; if (v < 0) v += MOD; return *this;}
    ModInt &operator *= (const ModInt &other) {v = v * other.v % MOD; return *this;}
    ModInt &operator /= (const ModInt &other) {return *this *= inverse (other);}
    bool operator == (const ModInt &other) const {return v == other.v;}
    bool operator != (const ModInt &other) const {return v != other.v;}
    bool operator < (const ModInt &other) const {return v < other.v;}
    bool operator > (const ModInt &other) const {return v > other.v;}
    friend ModInt operator + (ModInt a, const ModInt &b) {return a += b;}
    friend ModInt operator - (ModInt a, const ModInt &b) {return a -= b;}
    friend ModInt operator * (ModInt a, const ModInt &b) {return a *= b;}
    friend ModInt operator / (ModInt a, const ModInt &b) {return a /= b;}
    friend ModInt operator - (const ModInt &a) {return 0 - a;}
    friend ModInt power (ModInt a, long long b) {ModInt ret (1); while (b > 0) {if (b & 1) ret *= a; a *= a; b >>= 1;} return ret;}
    friend ModInt inverse (ModInt a) {return power (a, MOD - 2);}
    friend istream &operator >> (istream &is, ModInt &m) {is >> m.v; m.v = (-MOD < m.v && m.v < MOD) ? m.v : m.v % MOD; if (m.v < 0) m.v += MOD; return is;}
    friend ostream &operator << (ostream &os, const ModInt &m) {return os << m.v;}
};
using Mint = ModInt<mod>;
/*Mint a=2;
 * cout<<power(a,3);
 * assert(a*inverse(a)==1)
 */

endsnippet
snippet lamda "lamda"
auto $ {1: dfs} = [&] (auto &&$1) {

};
```
```cpp
// Author : md_nihal

#include "bits/stdc++.h"
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2,fma")

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef unsigned long long ull;
#define endl "\n"
#define vi vector<int>
#define pii pair<int,int>
#define vpi vector<pii>
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
using i_64 = int64_t;
const int mod = 1e9 + 7, inf = LONG_LONG_MAX, N = 1e6 + 7, MAX = 1e14 + 4;

/*----------------------------------------------- PBDS --------------------------------------------*/

using namespace __gnu_pbds;
template<typename T, typename Compare = std::greater<T>>
using heap = std::priority_queue<T, std::vector<T>, Compare>;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
template<class key, class value, class cmp = less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;

/*----------------------------------------------- PBDS ends --------------------------------------------*/
```
