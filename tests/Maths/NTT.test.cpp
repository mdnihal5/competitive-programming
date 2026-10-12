// NTT::multiply(a, b): convolution mod 998244353, O(n log n). Inputs must be reduced into [0, MOD);
// result size |a| + |b| - 1 (<= 2^23). Empty input gives empty output.
// Usage: vector<int> c = NTT::multiply(a, b);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Maths/NTT.cpp"
/* Usage:
 *   vector<int> c = NTT::multiply(a, b);   // a[i], b[i] already reduced mod 998244353
 */

int32_t main() {
    mt19937 rng(3);
    assert(NTT::multiply({}, {1}).empty());
    for (int it = 0; it < 200; it++) {
        int p = 1 + rng() % 40, q = 1 + rng() % 40;
        vector<int> x(p), y(q), want(p + q - 1);
        for (auto &v : x) v = rng() % 998244353;
        for (auto &v : y) v = rng() % 998244353;
        for (int i = 0; i < p; i++) for (int j = 0; j < q; j++) want[i + j] = (want[i + j] + x[i] * y[j]) % 998244353;
        assert(NTT::multiply(x, y) == want);
    }
    // (1 + 2x) * (3 + 4x) = 3 + 10x + 8x^2
    vector<int> a = {1, 2}, b = {3, 4};
    auto c = NTT::multiply(a, b);
    vector<int> expected = {3, 10, 8};
    assert(c == expected);

    // bigger check: (1+x+x^2+...+x^9)^2, coefficient k = min(k+1, 19-k) for k in [0,18]
    vector<int> ones(10, 1);
    auto sq = NTT::multiply(ones, ones);
    for (int k = 0; k < 19; k++) assert(sq[k] == min(k + 1, 19 - k));

    cout << "NTT OK\n";
}
