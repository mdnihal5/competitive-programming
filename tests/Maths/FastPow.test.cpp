// FastPow: unsigned 64-bit modpow/mulmod via __uint128_t (any m < 2^63), O(log e).
// inverse(n, m) works for any m (not just prime) as long as gcd(n, m) == 1. For operator syntax use ModInt.
// Usage: FastPow::power(b, e, m); FastPow::inverse(n, m);
#include "bits/stdc++.h"
using namespace std;
#define int long long

#include "../../lib/Maths/FastPow.cpp"
/* Usage:
 *   FastPow::power(b, e, m);      // b^e mod m, any m that fits in unsigned long long
 *   FastPow::inverse(n, m);       // n^-1 mod m, requires gcd(n, m) == 1
 *   // fixed compile-time modulus + ergonomic operators: use ModInt.cpp's Modular<MOD> instead
 */

int32_t main() {
    assert(FastPow::inverse(3, 1) == 0 && FastPow::inverse(1, 2) == 1 && FastPow::inverse(3, 8) == 3);
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
