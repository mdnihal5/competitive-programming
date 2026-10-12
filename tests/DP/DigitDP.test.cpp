// DigitDP: count integers in [0, bound] with digit sum <= K; state (pos, sum), non-tight memoised.
// Add problem state to solve()/memo and the end test at pos == size. Range [L,R]: count(R) - count(L-1)
// (negative bound is not supported, guard L=0).
// Usage: DigitDP dp(bound, K); int ans = dp.count();
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/DP/DigitDP.cpp"
/* Usage:
 *   DigitDP dp(bound, K);
 *   int answer = dp.count();     // # of integers in [0, bound] with digit sum <= K
 *   // For a range [L, R]: count(R) - count(L-1), same as any prefix-counting trick.
 */

static int bruteDigitSum(long long x) {
    int s = 0;
    while (x) { s += x % 10; x /= 10; }
    return s;
}

int32_t main() {
    for (int bound : {0LL, 1LL, 9LL, 10LL, 99LL, 100LL, 12345LL, 99999LL})
        for (int k : {0LL, 1LL, 7LL, 20LL, 45LL}) {
            int b = 0;
            for (int x = 0; x <= bound; x++) b += bruteDigitSum(x) <= k;
            assert(DigitDP(bound, k).count() == b);
        }
    long long bound = 500;
    int K = 5;
    DigitDP dp(bound, K);
    int fast = dp.count();

    int brute = 0;
    for (long long x = 0; x <= bound; x++) if (bruteDigitSum(x) <= K) brute++;

    assert(fast == brute);
    cout << "DigitDP OK (" << fast << " numbers in [0," << bound << "] with digit sum <= " << K << ")\n";
}
