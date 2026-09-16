// Author : md_nihal
// Source/adapted-from: linear sieve (cp-algorithms.com/algebra/prime-sieve-linear.html),
// replacing the old odd-skip Eratosthenes sieve here.
// Two real bugs fixed vs. the old version:
//   1. old version used GLOBAL bool marked[N]/int sp[N] -- collides if any other
//      pasted snippet also declares a global `marked`/`sp`. Now a struct, zero
//      global state.
//   2. old version's sp[] was `int`, which under this template's `#define int
//      long long` is 8 bytes/entry. Sized at N (1e5) that's fine, but the SAME
//      pattern sized at MAX (1e7) would be 80MB for one array -- likely blows a
//      256MB limit once combined with anything else. sp[] here is int32_t: a
//      prime's index/value always fits in 32 bits well past any sieve size a
//      contest will ask for.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct Sieve {
    int32_t limit;
    vector<int32_t> spf;    // spf[i] = smallest prime factor of i
    vector<int32_t> primes; // all primes <= limit, ascending

    explicit Sieve(int32_t n) : limit(n), spf(n + 1, 0) {
        for (int32_t i = 2; i <= n; i++) {
            if (spf[i] == 0) { spf[i] = i; primes.push_back(i); }
            for (int32_t p : primes) {
                if (p > spf[i] || (long long)p * i > n) break;
                spf[p * i] = p;
            }
        }
    }

    bool isPrime(int32_t x) const { return x >= 2 && spf[x] == x; }

    // prime factors of x with multiplicity, ascending, O(log x)
    vector<int32_t> factorize(int32_t x) const {
        vector<int32_t> f;
        while (x > 1) { f.push_back(spf[x]); x /= spf[x]; }
        return f;
    }
};
/* Usage:
 *   Sieve sv(1000000);                 // sieve up to 1e6 -- size to what you actually need, not MAX by habit
 *   bool p = sv.isPrime(97);           // true
 *   vector<int32_t> f = sv.factorize(360); // {2,2,2,3,3,5}
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    Sieve sv(1000);
    assert(sv.isPrime(2) && sv.isPrime(97) && sv.isPrime(997));
    assert(!sv.isPrime(1) && !sv.isPrime(0) && !sv.isPrime(999));

    vector<int32_t> f = sv.factorize(360);
    vector<int32_t> expected = {2, 2, 2, 3, 3, 5};
    assert(f == expected);

    int cnt = 0;
    for (int32_t i = 2; i <= 1000; i++) if (sv.isPrime(i)) cnt++;
    assert(cnt == (int)sv.primes.size());
    assert(cnt == 168); // known: pi(1000) = 168

    cout << "Sieve OK\n";
}
#endif
