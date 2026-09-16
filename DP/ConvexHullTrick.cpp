// Author : md_nihal
// Source/adapted-from: KACTL data-structures/LineContainer.h

#include "bits/stdc++.h"
using namespace std;
#define int long long
const int inf = 1E18;

/* ---- SNIPPET START ---- */
struct Line {
    mutable int k, m, p; // p = x where this line is overtaken by the next one
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(int x) const { return p < x; }
};

// maintains the upper envelope of lines y = k*x + m; query(x) returns the max.
// for a MIN envelope, negate k and m on every add(), then negate the query result.
struct LineContainer : multiset<Line, less<>> {
    static int div(int a, int b) { return a / b - ((a ^ b) < 0 && a % b); } // floored division

    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }

    void add(int k, int m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }

    int query(int x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
/* Usage:
 *   LineContainer lc;
 *   lc.add(k, m);            // insert line y = k*x + m
 *   lc.query(x);              // max over all inserted lines at x
 *   // for MIN: lc.add(-k, -m), then -lc.query(x)
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    LineContainer lc;
    lc.add(2, 3);   // y = 2x + 3
    lc.add(-1, 10); // y = -x + 10
    // at x=0: max(3, 10) = 10 ; at x=10: max(23, 0) = 23
    assert(lc.query(0) == 10);
    assert(lc.query(10) == 23);

    // brute-force cross-check: random lines, random query points, vs naive max
    mt19937 rng(11);
    for (int iter = 0; iter < 300; iter++) {
        LineContainer fast;
        vector<pair<int, int>> lines;
        int m = 1 + rng() % 30;
        for (int i = 0; i < m; i++) {
            int k = (int)(rng() % 2001) - 1000;
            int mm = (int)(rng() % 2001) - 1000;
            fast.add(k, mm);
            lines.push_back({k, mm});
        }
        for (int q = 0; q < 20; q++) {
            int x = (int)(rng() % 201) - 100;
            int brute = LLONG_MIN;
            for (auto &[k, mm] : lines) brute = max(brute, k * x + mm);
            assert(fast.query(x) == brute);
        }
    }

    cout << "OK\n";
}
#endif
