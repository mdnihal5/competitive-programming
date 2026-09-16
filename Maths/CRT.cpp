// Author : md_nihal
// Source/adapted-from: KACTL number-theory/CRT.h (extended-Euclid based)
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
// returns {g, x, y} with a*x + b*y = g = gcd(a, b)
tuple<int, int, int> extGcd(int a, int b) {
    if (!b) return {a, 1, 0};
    auto [g, x1, y1] = extGcd(b, a % b);
    return {g, y1, x1 - (a / b) * y1};
}

// Solve x = a (mod m), x = b (mod n). Returns {x, lcm(m, n)} with 0 <= x < lcm.
// Asserts a solution exists — does NOT silently return garbage on an infeasible
// system (e.g. x=0 mod 2 and x=1 mod 4 have no solution).
pair<int, int> crt(int a, int m, int b, int n) {
    auto [g, p, q] = extGcd(m, n);
    (void)q;
    assert((a - b) % g == 0 && "crt: no solution -- congruences are inconsistent");
    int lcm = m / g * n;
    int x = (a + m * (p * (((b - a) / g % (n / g) + (n / g)) % (n / g)))) % lcm;
    if (x < 0) x += lcm;
    return {x, lcm};
}
/* Usage:
 *   auto [x, L] = crt(a, m, b, n);   // x = a (mod m) and x = b (mod n), 0 <= x < L
 *   // for k > 2 congruences fold pairwise: r = crt(a1,m1,a2,m2); r = crt(r.first,r.second,a3,m3); ...
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    // x = 2 (mod 3), x = 3 (mod 5)  ->  x = 8 (mod 15)
    auto [x, L] = crt(2, 3, 3, 5);
    assert(x == 8 && L == 15);

    // x = 4 (mod 6), x = 1 (mod 9) -> lcm=18; check both congruences directly
    auto [x2, L2] = crt(4, 6, 1, 9);
    assert(L2 == 18 && x2 % 6 == 4 && x2 % 9 == 1);

    cout << "CRT OK\n";
}
#endif
