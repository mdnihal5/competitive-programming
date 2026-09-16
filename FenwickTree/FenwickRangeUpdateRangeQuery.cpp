// Author : md_nihal
// Source/adapted-from: standard two-BIT range-update range-query trick
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct FenwickRURQ {
    int n;
    vector<int> t1, t2;
    FenwickRURQ(int n) : n(n), t1(n + 1, 0), t2(n + 1, 0) {}
    void addTo(vector<int> &t, int idx, int val) {
        for (; idx <= n; idx += idx & -idx) t[idx] += val;
    }
    void update(int l, int r, int val) { // 0-indexed inclusive
        int l1 = l + 1, r1 = r + 1;
        addTo(t1, l1, val); addTo(t1, r1 + 1, -val);
        addTo(t2, l1, val * l1); addTo(t2, r1 + 1, -val * (r1 + 1));
    }
    int prefix(int k) { // sum a[0..k], 0-indexed inclusive
        int k1 = k + 1, s1 = 0, s2 = 0;
        for (int i = k1; i > 0; i -= i & -i) s1 += t1[i];
        for (int i = k1; i > 0; i -= i & -i) s2 += t2[i];
        return (k1 + 1) * s1 - s2;
    }
    int query(int l, int r) { return prefix(r) - (l ? prefix(l - 1) : 0); }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(888);
    int n = 15;
    FenwickRURQ f(n);
    vector<int> a(n, 0);
    for (int iter = 0; iter < 3000; iter++) {
        int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
        if (rng() % 2 == 0) {
            int v = (int)(rng() % 21) - 10;
            f.update(l, r, v);
            for (int i = l; i <= r; i++) a[i] += v;
        } else {
            int expect = 0; for (int i = l; i <= r; i++) expect += a[i];
            assert(f.query(l, r) == expect);
        }
    }
    cout << "OK\n";
}
#endif
