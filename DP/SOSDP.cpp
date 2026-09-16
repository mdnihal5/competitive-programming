// Author : md_nihal
// Source/adapted-from: cp-algorithms.com/algebra/all-submasks.html (Sum over Subsets)
// Toy example: given f[mask] for every mask in [0, 2^n), compute g[mask] = sum of
// f[sub] over every submask `sub` of `mask`. The one thing worth actually
// understanding here (not just pasting): iterating bit-then-mask, not
// mask-then-bit, is what makes this O(n * 2^n) instead of O(3^n) -- each mask
// gets "fixed" one bit at a time across n full passes, rather than every mask
// enumerating its own submasks independently.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
// g[mask] = sum over all submasks `sub` (sub & mask == sub) of f[sub]. O(n * 2^n).
vector<int> sos(vector<int> f) {                          // CHANGE THIS: combine op (here: sum) if not addition
    int sz = (int)f.size();
    int n = __builtin_ctz(sz == 1 ? 2 : sz);               // sz must be a power of two: n = log2(sz)
    vector<int> g = move(f);
    for (int bit = 0; bit < n; bit++) {
        for (int mask = 0; mask < sz; mask++) {
            if (mask & (1 << bit)) g[mask] += g[mask ^ (1 << bit)];  // CHANGE THIS: e.g. max/xor instead of +=
        }
    }
    return g;
}
/* Usage:
 *   vector<int> g = sos(f);   // f.size() must be a power of two (2^n); g[mask] = sum_{sub subseteq mask} f[sub]
 *   // For superset-sum instead of submask-sum: flip the condition to
 *   // `if (!(mask & (1<<bit)))` and combine mask with mask|(1<<bit).
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
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
    int n = 5, sz = 1 << n;
    vector<int> f(sz);
    mt19937 rng(42);
    for (int i = 0; i < sz; i++) f[i] = (int)(rng() % 100);

    auto fast = sos(f);
    auto brute = bruteSOS(f);
    assert(fast == brute);

    cout << "SOSDP OK\n";
}
#endif
