// Author : md_nihal
// Source/adapted-from: existing repo, consolidated (MergeSortTree2.cpp + temp.cpp were overlapping)
// static build only -- point update would need an O(n log n) resort per node, not offered here
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct MergeSortTree {
    int n;
    vector<vector<int>> t;
    MergeSortTree(const vector<int> &a) : n(a.size()), t(4 * n) { build(a, 1, 0, n - 1); }
    void build(const vector<int> &a, int node, int l, int r) {
        if (l == r) { t[node] = {a[l]}; return; }
        int m = (l + r) / 2;
        build(a, 2 * node, l, m); build(a, 2 * node + 1, m + 1, r);
        merge(all(t[2 * node]), all(t[2 * node + 1]), back_inserter(t[node]));
    }
    int countLess_(int node, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return lower_bound(all(t[node]), x) - t[node].begin();
        int m = (l + r) / 2;
        return countLess_(2 * node, l, m, ql, qr, x) + countLess_(2 * node + 1, m + 1, r, ql, qr, x);
    }
    int countLess(int l, int r, int x) { return countLess_(1, 0, n - 1, l, r, x); } // count a[i] < x
    int predecessor_(int node, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql) return INT_MIN;
        if (ql <= l && r <= qr) {
            auto it = upper_bound(all(t[node]), x);
            return it == t[node].begin() ? INT_MIN : *prev(it);
        }
        int m = (l + r) / 2;
        return max(predecessor_(2 * node, l, m, ql, qr, x), predecessor_(2 * node + 1, m + 1, r, ql, qr, x));
    }
    int predecessor(int l, int r, int x) { return predecessor_(1, 0, n - 1, l, r, x); } // largest a[i] <= x, else INT_MIN
    int successor_(int node, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql) return INT_MAX;
        if (ql <= l && r <= qr) {
            auto it = lower_bound(all(t[node]), x);
            return it == t[node].end() ? INT_MAX : *it;
        }
        int m = (l + r) / 2;
        return min(successor_(2 * node, l, m, ql, qr, x), successor_(2 * node + 1, m + 1, r, ql, qr, x));
    }
    int successor(int l, int r, int x) { return successor_(1, 0, n - 1, l, r, x); } // smallest a[i] >= x, else INT_MAX
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(6767);
    int n = 25;
    vector<int> a(n);
    for (auto &x : a) x = rng() % 50;
    MergeSortTree t(a);

    for (int iter = 0; iter < 2000; iter++) {
        int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
        int x = rng() % 50;

        int ecnt = 0; for (int i = l; i <= r; i++) if (a[i] < x) ecnt++;
        assert(t.countLess(l, r, x) == ecnt);

        int epred = INT_MIN; for (int i = l; i <= r; i++) if (a[i] <= x) epred = max(epred, a[i]);
        assert(t.predecessor(l, r, x) == epred);

        int esucc = INT_MAX; for (int i = l; i <= r; i++) if (a[i] >= x) esucc = min(esucc, a[i]);
        assert(t.successor(l, r, x) == esucc);
    }
    cout << "OK\n";
}
#endif
