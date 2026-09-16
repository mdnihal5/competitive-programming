// Author : md_nihal
// Source/adapted-from: cp-algorithms.com/algebra/euler-totient.html
// Deliberately self-contained trial division, O(sqrt(n)), rather than reusing
// Maths/primes.cpp's Sieve — that would make this snippet depend on another
// struct being pasted and constructed first, which is exactly the kind of
// cross-file coupling the "don't break mid-contest" rule rules out. If you
// need phi(1..K) for MANY values up to a large K, sieve it instead (batch, not
// this function) — that's a different tool for a different access pattern.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
// Euler's totient phi(n): count of integers in [1, n] coprime to n.
int phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}
/* Usage:
 *   int f = phi(36);   // -> 12
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    assert(phi(1) == 1);
    assert(phi(9) == 6);
    assert(phi(36) == 12);
    assert(phi(17) == 16); // prime p -> phi(p) = p-1
    assert(phi(1000000) == 400000);

    cout << "Totient OK\n";
}
#endif
