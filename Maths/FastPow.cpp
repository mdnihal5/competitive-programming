// Author : md_nihal
// Source/adapted-from: existing repo (Maths/powers.cpp) -- fixed a real bug:
// euclid() used an undeclared type `Lint` (never compiled). Namespaced to avoid
// colliding with ModInt.cpp's power()/inverse() (different signatures: this one
// takes the modulus at runtime, for when it isn't a compile-time constant).

#include "bits/stdc++.h"
using namespace std;
#define int long long

/* ---- SNIPPET START ---- */
namespace FastPow {
using ull = unsigned long long;

// __int128-based mulmod: correct for any mod that fits in ull, no floating-point
// trick to trust or get subtly wrong.
ull mulmod(ull a, ull b, ull m) { return (__uint128_t)a * b % m; }

ull power(ull b, ull e, ull m) {
    ull ans = 1 % m;
    for (b %= m; e; e >>= 1, b = mulmod(b, b, m))
        if (e & 1) ans = mulmod(ans, b, m);
    return ans;
}

// x*a + y*b = gcd(a,b)
void extGcd(ull a, ull b, long long &x, long long &y) {
    if (!b) { x = 1; y = 0; return; }
    long long x1, y1;
    extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (long long)(a / b) * y1;
}

// modular inverse of n mod m, requires gcd(n, m) == 1
ull inverse(ull n, ull m) {
    long long x, y;
    extGcd(m, n % m, x, y);
    return ((y % (long long)m) + (long long)m) % m;
}
}
/* Usage:
 *   FastPow::power(b, e, m);      // b^e mod m, any m that fits in unsigned long long
 *   FastPow::inverse(n, m);       // n^-1 mod m, requires gcd(n, m) == 1
 *   // fixed compile-time modulus + ergonomic operators: use ModInt.cpp's Modular<MOD> instead
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    assert(FastPow::power(2, 10, 1000000007ULL) == 1024);
    assert(FastPow::power(3, 0, 5) == 1);
    assert(FastPow::power(7, 1, 1000000007ULL) == 7);

    // large modulus, well beyond what a naive 64-bit a*b%m would handle safely
    FastPow::ull bigMod = 999999999999999989ULL; // large prime
    FastPow::ull r = FastPow::power(123456789, 987654321, bigMod);
    __uint128_t check = 1, base = 123456789 % bigMod;
    FastPow::ull e = 987654321;
    while (e) { if (e & 1) check = check * base % bigMod; base = base * base % bigMod; e >>= 1; }
    assert(r == (FastPow::ull)check);

    // inverse correctness: n * inverse(n) == 1 mod m, for many random coprime pairs
    mt19937_64 rng(99);
    FastPow::ull m = 1000000007ULL;
    for (int i = 0; i < 500; i++) {
        FastPow::ull n = 1 + rng() % (m - 1);
        FastPow::ull inv = FastPow::inverse(n, m);
        assert(FastPow::mulmod(n, inv, m) == 1);
    }

    cout << "OK\n";
}
#endif
