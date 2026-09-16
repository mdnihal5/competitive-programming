// Author : md_nihal
// Source/adapted-from: existing repo, consolidated (RangeMinQuery.cpp + RMQ.cpp were duplicates)
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
template<typename T, typename F>
struct SparseTable {
    vector<vector<T>> sp;
    vector<int> lg;
    F combine;
    // combine must be idempotent + associative (min/max/gcd/and/or -- NOT sum)
    SparseTable(const vector<T> &a, F combine) : combine(combine) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = lg[n] + 1;
        sp.assign(K, vector<T>(n));
        sp[0] = a;
        for (int j = 1; j < K; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                sp[j][i] = combine(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
    }
    T query(int l, int r) {
        int k = lg[r - l + 1];
        return combine(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(4242);
    int n = 40;
    vector<int> a(n);
    for (auto &x : a) x = rng() % 100;

    SparseTable st_min(a, [](int x, int y) { return min(x, y); });
    SparseTable st_gcd(a, [](int x, int y) { return __gcd(x, y); });

    for (int iter = 0; iter < 2000; iter++) {
        int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
        int emin = a[l], egcd = a[l];
        for (int i = l + 1; i <= r; i++) { emin = min(emin, a[i]); egcd = __gcd(egcd, a[i]); }
        assert(st_min.query(l, r) == emin);
        assert(st_gcd.query(l, r) == egcd);
    }
    cout << "OK\n";
}
#endif
