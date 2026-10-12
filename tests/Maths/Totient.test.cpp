// phi(n): Euler totient by trial division, O(sqrt n). phi(1) = 1.
// Usage: int f = phi(n);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Maths/Totient.cpp"
/* Usage:
 *   int f = phi(36);   // -> 12
 */

int32_t main() {
    for (int n = 1; n <= 500; n++) {
        int c = 0;
        for (int k = 1; k <= n; k++) c += __gcd(n, k) == 1;
        assert(phi(n) == c);
    }
    assert(phi(1) == 1);
    assert(phi(9) == 6);
    assert(phi(36) == 12);
    assert(phi(17) == 16); // prime p -> phi(p) = p-1
    assert(phi(1000000) == 400000);

    cout << "Totient OK\n";
}
