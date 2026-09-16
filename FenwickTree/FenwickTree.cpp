// Author : md_nihal
// Source/adapted-from: existing repo, consolidated
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct Fenwick {
    int n;
    vector<int> t;
    Fenwick(int n) : n(n), t(n + 1, 0) {}
    void update(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx) t[idx] += val;
    }
    int query(int idx) {
        int s = 0;
        for (++idx; idx > 0; idx -= idx & -idx) s += t[idx];
        return s;
    }
    int query(int l, int r) { return query(r) - (l ? query(l - 1) : 0); }
    // 0-indexed; requires all updates so far non-negative
    int lower_bound(int val) {
        int pos = 0, sum = 0;
        for (int i = __lg(n) + 1; i >= 0; i--) {
            int nxt = pos + (1LL << i);
            if (nxt <= n && sum + t[nxt] < val) { pos = nxt; sum += t[nxt]; }
        }
        return pos;
    }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(12345);
    {
        Fenwick f(10);
        vector<int> a(10, 0);
        for (int iter = 0; iter < 2000; iter++) {
            int op = rng() % 2;
            if (op == 0) {
                int idx = rng() % 10, val = (int)(rng() % 21) - 10;
                f.update(idx, val); a[idx] += val;
            } else {
                int l = rng() % 10, r = rng() % 10; if (l > r) swap(l, r);
                int expect = 0; for (int i = l; i <= r; i++) expect += a[i];
                assert(f.query(l, r) == expect);
            }
        }
    }
    {
        int n = 12;
        Fenwick f(n);
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) { int v = rng() % 5; f.update(i, v); a[i] = v; }
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
        for (int val = 0; val <= pref[n] + 2; val++) {
            int expect = n; // if never reached, brute returns n (no valid index)
            for (int i = 0; i < n; i++) if (pref[i + 1] >= val) { expect = i; break; }
            assert(f.lower_bound(val) == expect);
        }
    }
    cout << "OK\n";
}
#endif
