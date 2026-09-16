// Author : md_nihal
// Source/adapted-from: KACTL numerical/NumberTheoreticTransform.h
// Fixed NTT-friendly prime only (998244353 = 119*2^23+1, primitive root 3).
// Swapping in an arbitrary modulus does NOT work with this version -- that
// needs a separate three-NTT-and-CRT combine (not provided here). If a problem
// forces a different modulus and you don't have that trick handy, fall back to
// classic FFT with doubles and round at the end.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
namespace NTT {
constexpr int MOD = 998244353, ROOT = 3;

int power(int a, int e, int m) {
    int r = 1; a %= m; if (a < 0) a += m;
    for (; e; e >>= 1, a = a * a % m) if (e & 1) r = r * a % m;
    return r;
}

void transform(vector<int> &a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int w = power(ROOT, (MOD - 1) / len, MOD);
        if (invert) w = power(w, MOD - 2, MOD);
        for (int i = 0; i < n; i += len) {
            int wn = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (invert) {
        int nInv = power(n, MOD - 2, MOD);
        for (int &x : a) x = x * nInv % MOD;
    }
}

// polynomial multiplication mod 998244353; result size = |a|+|b|-1, coefficients pre-reduced mod MOD
vector<int> multiply(vector<int> a, vector<int> b) {
    int resultSize = (int)a.size() + (int)b.size() - 1, n = 1;
    while (n < resultSize) n <<= 1;
    a.resize(n); b.resize(n);
    transform(a, false); transform(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    transform(a, true);
    a.resize(resultSize);
    return a;
}
}
/* Usage:
 *   vector<int> c = NTT::multiply(a, b);   // a[i], b[i] already reduced mod 998244353
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
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
#endif
