// Author : md_nihal
// Synced to match the live UltiSnips `ModInt` snippet exactly (the repo copy had
// drifted -- different method names, mexp/pow instead of power -- fixed so the
// repo and the daily-use snippet never disagree again).

#include "bits/stdc++.h"
using namespace std;
#define int long long

/* ---- SNIPPET START ---- */
template <int MOD = 998244353>
struct Modular {
    int value;
    Modular(long long v = 0) { value = v % MOD; if (value < 0) value += MOD; }
    Modular(long long a, long long b) : value(0) { *this += a; *this /= b; }

    Modular &operator+=(const Modular &b) { value += b.value; if (value >= MOD) value -= MOD; return *this; }
    Modular &operator-=(const Modular &b) { value -= b.value; if (value < 0) value += MOD; return *this; }
    Modular &operator*=(const Modular &b) { value = (long long)value * b.value % MOD; return *this; }

    friend Modular power(Modular a, long long e) {
        Modular r = 1;
        for (; e; e >>= 1, a *= a) if (e & 1) r *= a;
        return r;
    }
    friend Modular inverse(Modular a) { return power(a, MOD - 2); }

    Modular &operator/=(const Modular &b) { return *this *= inverse(b); }
    friend Modular operator+(Modular a, const Modular &b) { return a += b; }
    friend Modular operator-(Modular a, const Modular &b) { return a -= b; }
    friend Modular operator-(const Modular &a) { return 0 - a; }
    friend Modular operator*(Modular a, const Modular &b) { return a *= b; }
    friend Modular operator/(Modular a, const Modular &b) { return a /= b; }
    friend std::ostream &operator<<(std::ostream &os, const Modular &a) { return os << a.value; }
    friend bool operator==(const Modular &a, const Modular &b) { return a.value == b.value; }
    friend bool operator!=(const Modular &a, const Modular &b) { return a.value != b.value; }
};

using mint = Modular<998244353>;
/* Usage:
 *   mint a = 2;
 *   cout << power(a, 3);          // 8
 *   assert(a * inverse(a) == 1);
 *   // different fixed modulus: using mint2 = Modular<1'000'000'007>;
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
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
#endif
