// Sieve: linear sieve up to n, O(n). spf = smallest prime factor, primes ascending. isPrime/factorize need
// x <= n; factorize is O(log x) with multiplicity. Stored as int32 on purpose (memory for n ~ 1e7).
// Usage: Sieve sv(n); sv.isPrime(x); sv.factorize(x); sv.primes;
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Maths/primes.cpp"
/* Usage:
 *   Sieve sv(1000000);                 // sieve up to 1e6 -- size to what you actually need, not MAX by habit
 *   bool p = sv.isPrime(97);           // true
 *   vector<int32_t> f = sv.factorize(360); // {2,2,2,3,3,5}
 */

int32_t main() {
    Sieve big(2000000);
    for (int x : {2, 3, 4, 1999993, 1999999, 1048576, 1999998}) {
        auto f = big.factorize(x);
        int prod = 1;
        for (int p : f) { prod *= p; assert(big.isPrime(p)); }
        assert(prod == x);
    }
    assert(Sieve(0).primes.empty() && Sieve(1).primes.empty() && Sieve(2).primes.size() == 1);
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
