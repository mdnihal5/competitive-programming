// crt(a, m, b, n): x = a (mod m), x = b (mod n), moduli need not be coprime; returns {x, lcm}, 0 <= x < lcm.
// Asserts when the system is inconsistent; lcm and m*n/g must fit in 64 bits. Fold pairwise for k > 2.
// Usage: auto [x, L] = crt(a, m, b, n);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Maths/CRT.cpp"
/* Usage:
 *   auto [x, L] = crt(a, m, b, n);   // x = a (mod m) and x = b (mod n), 0 <= x < L
 *   // for k > 2 congruences fold pairwise: r = crt(a1,m1,a2,m2); r = crt(r.first,r.second,a3,m3); ...
 */

int32_t main() {
    mt19937 rng(17);
    for (int it = 0; it < 3000; it++) {
        int m = 1 + rng() % 30, n = 1 + rng() % 30, a = rng() % 60, b = rng() % 60;
        int g = __gcd(m, n);
        bool ok = (a % g) == (b % g);
        if (!ok) continue;
        auto [r, l] = crt(a, m, b, n);
        assert(l == m / g * n && 0 <= r && r < l && r % m == a % m && r % n == b % n);
    }
    {
        int m = 1000000007, n = 998244353;
        auto [r, l] = crt(123456789, m, 987654321, n);
        assert(l == m * n && r % m == 123456789 && r % n == 987654321);
        auto [r2, l2] = crt(-5, 1000000000, 999999999, 999999937);
        assert(l2 == 1000000000LL * 999999937 && r2 % 1000000000 == 999999995 && r2 % 999999937 == 999999999 % 999999937);
    }
    // x = 2 (mod 3), x = 3 (mod 5)  ->  x = 8 (mod 15)
    auto [x, L] = crt(2, 3, 3, 5);
    assert(x == 8 && L == 15);

    // x = 4 (mod 6), x = 1 (mod 9) -> lcm=18; check both congruences directly
    auto [x2, L2] = crt(4, 6, 1, 9);
    assert(L2 == 18 && x2 % 6 == 4 && x2 % 9 == 1);

    cout << "CRT OK\n";
}
