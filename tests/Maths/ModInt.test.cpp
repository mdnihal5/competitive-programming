// Modular<MOD>: MOD must be prime (division uses Fermat), +,-,*,/ , power(a, e >= 0), inverse(a), cin/cout.
// Usage: mint a = 2; cout << power(a, 3) << a / 5; using mint2 = Modular<1000000007>;
#include "bits/stdc++.h"
using namespace std;
#define int long long

#include "../../lib/Maths/ModInt.cpp"
/* Usage:
 *   mint a = 2;
 *   cout << power(a, 3);          // 8
 *   assert(a * inverse(a) == 1);
 *   // different fixed modulus: using mint2 = Modular<1'000'000'007>;
 */

int32_t main() {
    assert((mint(1) / 3 * 3).value == 1 && (-mint(1)).value == 998244352 && mint(-1).value == 998244352);
    assert(power(mint(0), 0).value == 1 && power(mint(5), 3) == mint(125));
    mint a = 2;
    assert(power(a, 10).value == 1024);
    assert((a * inverse(a)).value == 1);
    mint b = 5, c = 3;
    assert((b + c).value == 8);
    assert((b - c).value == 2);
    assert((b * c).value == 15);

    using mint2 = Modular<1'000'000'007>;
    mint2 x = 1'000'000'006; // MOD - 1, i.e. -1
    assert((x + 1).value == 0);
    assert((x * x).value == 1); // (-1)*(-1) = 1

    cout << "OK\n";
}
