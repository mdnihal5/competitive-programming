// Author : md_nihal
// Pattern reference, not a fixed library: cp-algorithms.com/dynamic_programming/profile-dynamics.html
// and standard "count numbers <= N with property P" digit-DP shape.
// This is a SKELETON with a worked toy example filled in, not a drop-in struct --
// the state you add beyond (pos, tight) is always problem-specific. Lines marked
// // CHANGE THIS: are exactly what a real problem makes you edit.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
// Toy example: count integers in [0, bound] whose decimal digit sum is <= K.
struct DigitDP {
    string digits;                                   // decimal digits of the bound, most significant first
    int K;                                            // CHANGE THIS: whatever extra state your problem needs
    vector<vector<vector<int>>> memo;                 // memo[pos][tight][digitSumSoFar] -- CHANGE THIS: shape to your state

    DigitDP(long long bound, int k) : digits(to_string(bound)), K(k) {
        memo.assign(digits.size() + 1, vector<vector<int>>(2, vector<int>(9 * digits.size() + 1, -1)));
    }

    // pos = index into digits, tight = are we still bound by the prefix of `bound`,
    // sum = digit sum accumulated so far. Returns count of valid completions.
    int solve(int pos, bool tight, int sum) {
        if (pos == (int)digits.size()) return sum <= K;            // CHANGE THIS: base-case acceptance test
        if (!tight && memo[pos][0][sum] != -1) return memo[pos][0][sum];

        int limit = tight ? digits[pos] - '0' : 9;
        int total = 0;
        for (int d = 0; d <= limit; d++) {
            total += solve(pos + 1, tight && d == limit, sum + d);  // CHANGE THIS: how state evolves per digit
        }
        if (!tight) memo[pos][0][sum] = total;
        return total;
    }

    int count() { return solve(0, true, 0); }
};
/* Usage:
 *   DigitDP dp(bound, K);
 *   int answer = dp.count();     // # of integers in [0, bound] with digit sum <= K
 *   // For a range [L, R]: count(R) - count(L-1), same as any prefix-counting trick.
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
static int bruteDigitSum(long long x) {
    int s = 0;
    while (x) { s += x % 10; x /= 10; }
    return s;
}

int32_t main() {
    long long bound = 500;
    int K = 5;
    DigitDP dp(bound, K);
    int fast = dp.count();

    int brute = 0;
    for (long long x = 0; x <= bound; x++) if (bruteDigitSum(x) <= K) brute++;

    assert(fast == brute);
    cout << "DigitDP OK (" << fast << " numbers in [0," << bound << "] with digit sum <= " << K << ")\n";
}
#endif
