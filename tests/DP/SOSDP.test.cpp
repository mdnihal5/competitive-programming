// sos(f): g[mask] = sum of f[sub] over submasks sub of mask; f.size() must be a power of two. O(n * 2^n).
// Superset sum: test (mask & b) == 0 and add f[mask | b]. Other ops (max, xor): change the +=.
// Usage: vector<int> g = sos(f);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/DP/SOSDP.cpp"
/* Usage:
 *   vector<int> g = sos(f);   // f.size() must be a power of two (2^n); g[mask] = sum_{sub subseteq mask} f[sub]
 *   // For superset-sum instead of submask-sum: flip the condition to
 *   // `if (!(mask & (1<<bit)))` and combine mask with mask|(1<<bit).
 */

static vector<int> bruteSOS(const vector<int> &f) {
    int sz = (int)f.size();
    vector<int> g(sz, 0);
    for (int mask = 0; mask < sz; mask++)
        for (int sub = mask; ; sub = (sub - 1) & mask) {
            g[mask] += f[sub];
            if (sub == 0) break;
        }
    return g;
}

int32_t main() {
    for (int nn = 0; nn <= 8; nn++) {
        mt19937 r(nn);
        vector<int> h(1 << nn);
        for (auto &x : h) x = r() % 1000;
        assert(sos(h) == bruteSOS(h));
    }
    int n = 5, sz = 1 << n;
    vector<int> f(sz);
    mt19937 rng(42);
    for (int i = 0; i < sz; i++) f[i] = (int)(rng() % 100);

    auto fast = sos(f);
    auto brute = bruteSOS(f);
    assert(fast == brute);

    cout << "SOSDP OK\n";
}
