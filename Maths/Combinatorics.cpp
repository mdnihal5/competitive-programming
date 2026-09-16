// Author : md_nihal
// Source/adapted-from: existing repo (Maths/combinations.cpp, Maths/Math.cpp),
// replacing both. Fixed a real bug: the old nCr(a,b) returned 1 for C(0, b>0)
// (should be 0) and depended on a global fact[] array that was never filled in.

#include "bits/stdc++.h"
using namespace std;
#define int long long
const int mod = 1E9 + 7;

/* ---- SNIPPET START ---- */
struct Combinatorics {
    int n;
    vector<int> fac, inv, finv;

    Combinatorics(int maxN) : n(maxN), fac(maxN + 1), inv(maxN + 1), finv(maxN + 1) {
        fac[0] = inv[1] = finv[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
        for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;
        for (int i = 1; i <= n; i++) finv[i] = finv[i - 1] * inv[i] % mod;
    }

    int nCr(int a, int b) {
        if (b < 0 || b > a || a < 0) return 0;
        return fac[a] * finv[b] % mod * finv[a - b] % mod;
    }

    int nPr(int a, int b) {
        if (b < 0 || b > a || a < 0) return 0;
        return fac[a] * finv[a - b] % mod;
    }
};
/* Usage:
 *   Combinatorics C(200000);      // size to the largest n you'll query, not MAX by habit
 *   C.nCr(10, 3);                 // 120
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    Combinatorics C(1000);
    assert(C.nCr(10, 3) == 120);
    assert(C.nCr(5, 0) == 1);
    assert(C.nCr(0, 0) == 1);
    assert(C.nCr(0, 3) == 0);      // the exact case the old version got wrong
    assert(C.nCr(3, 5) == 0);      // b > a
    assert(C.nPr(5, 2) == 20);

    // brute-force cross-check against Pascal's triangle mod p, small n
    vector<vector<int>> pascal(61, vector<int>(61, 0));
    for (int i = 0; i <= 60; i++) {
        pascal[i][0] = 1;
        for (int j = 1; j <= i; j++)
            pascal[i][j] = (pascal[i - 1][j - 1] + (j <= i - 1 ? pascal[i - 1][j] : 0)) % mod;
    }
    Combinatorics C2(60);
    for (int i = 0; i <= 60; i++)
        for (int j = 0; j <= 60; j++)
            assert(C2.nCr(i, j) == pascal[i][j]);

    cout << "OK\n";
}
#endif
