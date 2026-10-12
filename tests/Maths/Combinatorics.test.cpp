// Combinatorics: factorial tables mod `mod` (must be a prime > maxN), O(maxN) build, O(1) nCr/nPr.
// Indices a must be <= maxN; out-of-range b gives 0.
// Usage: Combinatorics C(maxN); C.nCr(a, b); C.nPr(a, b);
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int mod = 1E9 + 7;

#include "../../lib/Maths/Combinatorics.cpp"
/* Usage:
 *   Combinatorics C(200000);      // size to the largest n you'll query, not MAX by habit
 *   C.nCr(10, 3);                 // 120
 */

int32_t main() {
    Combinatorics C0(0);
    assert(C0.nCr(0, 0) == 1 && C0.nCr(0, 1) == 0 && C0.nPr(0, 0) == 1);
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
