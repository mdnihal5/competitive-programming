// PersistentSegTree st(a, identity, combine): version 0 = a. 0-indexed.
// v2 = st.update(v, i, val) -> new version id (old versions stay valid); st.query(v, l, r) inclusive.
// Each update adds O(log n) nodes (total nodes <= 2n + updates*(log n + 1)); query O(log n).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/SegmentTree/PersistentSegmentTree.cpp"

int32_t main() {
    mt19937 rng(3434);
    for (int n = 1; n <= 20; n++) {
        vector<int> base(n);
        vector<string> sbase(n);
        for (int i = 0; i < n; i++) { base[i] = rng() % 20; sbase[i] = string(1, 'a' + rng() % 26); }
        PersistentSegTree st(base, 0LL, [](int x, int y) { return x + y; });
        PersistentSegTree sc(sbase, string(), [](string x, string y) { return x + y; });
        vector<vector<int>> versions = {base};
        vector<vector<string>> sversions = {sbase};
        int updates = 0;
        for (int iter = 0; iter < 60; iter++) {
            int from = rng() % versions.size(), idx = rng() % n, val = rng() % 20;
            string sv(1, 'a' + rng() % 26);
            int id = st.update(from, idx, val);
            assert(sc.update(from, idx, sv) == id && id == (int)versions.size());
            versions.push_back(versions[from]); versions.back()[idx] = val;
            sversions.push_back(sversions[from]); sversions.back()[idx] = sv;
            updates++;
        }
        assert((int)st.t.size() <= 2 * n + updates * (__lg(n) + 2));
        for (int v = 0; v < (int)versions.size(); v++)
            for (int q = 0; q < 5; q++) {
                int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
                int es = 0; string ec;
                for (int i = l; i <= r; i++) { es += versions[v][i]; ec += sversions[v][i]; }
                assert(st.query(v, l, r) == es);
                assert(sc.query(v, l, r) == ec);
            }
    }
    cout << "OK\n";
}
