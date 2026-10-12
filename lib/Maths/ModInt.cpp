template <int MOD = 998244353>
struct Modular {
    int value;
    Modular(long long v = 0) : value((v % MOD + MOD) % MOD) {}

    Modular &operator+=(const Modular &b) { value += b.value; if (value >= MOD) value -= MOD; return *this; }
    Modular &operator-=(const Modular &b) { value -= b.value; if (value < 0) value += MOD; return *this; }
    Modular &operator*=(const Modular &b) { value = value * b.value % MOD; return *this; }
    Modular &operator/=(const Modular &b) { return *this *= inverse(b); }

    friend Modular power(Modular a, long long e) {
        Modular r = 1;
        for (; e; e >>= 1, a *= a) if (e & 1) r *= a;
        return r;
    }
    friend Modular inverse(Modular a) { return power(a, MOD - 2); }
    friend Modular operator+(Modular a, const Modular &b) { return a += b; }
    friend Modular operator-(Modular a, const Modular &b) { return a -= b; }
    friend Modular operator*(Modular a, const Modular &b) { return a *= b; }
    friend Modular operator/(Modular a, const Modular &b) { return a /= b; }
    friend Modular operator-(const Modular &a) { return 0 - a; }
    friend bool operator==(const Modular &a, const Modular &b) { return a.value == b.value; }
    friend bool operator!=(const Modular &a, const Modular &b) { return a.value != b.value; }
    friend ostream &operator<<(ostream &os, const Modular &a) { return os << a.value; }
    friend istream &operator>>(istream &is, Modular &a) { long long v; is >> v; a = Modular(v); return is; }
};

using mint = Modular<998244353>;
