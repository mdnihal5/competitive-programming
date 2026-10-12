namespace FastPow {
using ull = unsigned long long;

ull mulmod(ull a, ull b, ull m) { return (__uint128_t)a * b % m; }

ull power(ull b, ull e, ull m) {
    ull ans = 1 % m;
    for (b %= m; e; e >>= 1, b = mulmod(b, b, m))
        if (e & 1) ans = mulmod(ans, b, m);
    return ans;
}

ull inverse(ull n, ull m) {
    long long a = n % m, b = m, x = 1, y = 0;
    while (b) {
        long long t = a / b;
        a -= t * b, swap(a, b);
        x -= t * y, swap(x, y);
    }
    return (x % (long long)m + m) % m;
}
}
