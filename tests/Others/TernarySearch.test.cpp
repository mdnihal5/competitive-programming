// ternarySearchMin(lo, hi, f): integer x in [lo, hi] minimising f; f strictly decreasing then strictly increasing
// (a flat run is allowed only at the minimum). For a maximum pass [&](int x){ return -f(x); }.
// Implemented as a binary search on the slope f(m) <= f(m+1): ~2*log2(range) evaluations, no plateau traps.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Others/TernarySearch.cpp"

int32_t main() {
    mt19937 rng(3);
    for (int iter = 0; iter < 3000; iter++) {
        int lo = (int)(rng() % 200) - 100, hi = lo + rng() % 150;
        int a = lo + rng() % (hi - lo + 1), b = a + rng() % 4;
        int sl = 1 + rng() % 5, sr = 1 + rng() % 5;
        auto f = [&](int x) { return x < a ? (a - x) * sl : x > b ? (x - b) * sr : 0; };
        int got = ternarySearchMin(lo, hi, f);
        int best = inf;
        for (int x = lo; x <= hi; x++) best = min(best, f(x));
        assert(lo <= got && got <= hi && f(got) == best);
    }
    auto g = [](int x) { return -(x - 3) * (x - 3) + 50; };
    assert(ternarySearchMin(-50, 50, [&](int x) { return -g(x); }) == 3);
    assert(ternarySearchMin(5, 5, [](int x) { return x; }) == 5);
    cout << "OK\n";
}
