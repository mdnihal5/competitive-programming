// FenwickRUPQ: 0-indexed inclusive range add, point read, O(log n).
// Usage: f.update(l, r, v); f.query(i);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/FenwickTree/FenwickRangeUpdatePointQuery.cpp"

int32_t main() {
    mt19937 rng(777);
    int n = 15;
    FenwickRUPQ f(n);
    vector<int> a(n, 0);
    for (int iter = 0; iter < 3000; iter++) {
        int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
        int v = (int)(rng() % 21) - 10;
        f.update(l, r, v);
        for (int i = l; i <= r; i++) a[i] += v;
        int idx = rng() % n;
        assert(f.query(idx) == a[idx]);
    }
    cout << "OK\n";
}
