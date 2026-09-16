// Author : md_nihal
// Source/adapted-from: existing repo (Others/ternarysearch.cpp) -- the old version
// was a raw code fragment copy-pasted from a specific submission, referencing
// undefined externals (solve/low/high). Rewritten as a real, generic template.

#include "bits/stdc++.h"
using namespace std;
#define int long long

/* ---- SNIPPET START ---- */
// Minimum of a unimodal (strictly-decreases-then-strictly-increases) integer
// function f over [lo, hi]. For a maximum, negate f (pass [&](int x){ return -f(x); }).
template <class F>
int ternarySearchMin(int lo, int hi, F f) {
    while (hi - lo > 2) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f(m1) <= f(m2)) hi = m2; else lo = m1;
    }
    int best = lo;
    for (int x = lo + 1; x <= hi; x++) if (f(x) < f(best)) best = x;
    return best;
}
/* Usage:
 *   int x = ternarySearchMin(lo, hi, [&](int x) { return f(x); });
 *   int fMin = f(x);
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    // f(x) = (x-7)^2, unimodal minimum at x=7
    auto f = [](int x) { return (x - 7) * (x - 7); };
    int x = ternarySearchMin(-100, 100, f);
    assert(x == 7);

    // maximum via negation: g(x) = -(x-3)^2 + 50, peak at x=3
    auto g = [](int x) { return -(x - 3) * (x - 3) + 50; };
    int xMax = ternarySearchMin(-50, 50, [&](int x) { return -g(x); });
    assert(xMax == 3);

    // brute-force cross-check on many random unimodal quadratics
    mt19937 rng(3);
    for (int iter = 0; iter < 200; iter++) {
        int peak = -50 + (int)(rng() % 101);
        int lo = peak - 1 - (int)(rng() % 50), hi = peak + 1 + (int)(rng() % 50);
        auto h = [&](int x) { return (x - peak) * (x - peak); };
        int got = ternarySearchMin(lo, hi, h);
        int expected = lo;
        for (int v = lo; v <= hi; v++) if (h(v) < h(expected)) expected = v;
        assert(h(got) == h(expected)); // ties (two x at same min value) are fine, value must match
    }

    cout << "OK\n";
}
#endif
