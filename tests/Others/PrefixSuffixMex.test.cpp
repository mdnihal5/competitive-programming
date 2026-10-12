// auto [pre, suf] = prefixSuffixMex(a): pre[i] = mex(a[0..i]), suf[i] = mex(a[i..n-1]).
// Negative or > n values are ignored (cannot affect the mex). O(n) time and memory.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Others/PrefixSuffixMex.cpp"

int naiveMex(vector<int> v) {
    sort(all(v));
    int m = 0;
    for (int x : v) { if (x == m) m++; else if (x > m) break; }
    return m;
}

int32_t main() {
    mt19937 rng(42);
    for (int iter = 0; iter < 1000; iter++) {
        int n = 1 + rng() % 14, hi = 1 + rng() % 10;
        vector<int> a(n);
        for (auto &x : a) x = (int)(rng() % (hi + 2)) - 1;
        if (rng() % 10 == 0) a[rng() % n] = 1000000000000LL;
        auto [pm, sm] = prefixSuffixMex(a);
        for (int i = 0; i < n; i++) {
            assert(pm[i] == naiveMex(vector<int>(a.begin(), a.begin() + i + 1)));
            assert(sm[i] == naiveMex(vector<int>(a.begin() + i, a.end())));
        }
    }
    assert(prefixSuffixMex({}).first.empty());
    cout << "OK\n";
}
