namespace combinations {
const int MAXN = 1000005; // Adjust the maximum value of n as needed
const int MOD = 1000000007; // Change the MOD value as needed
int fac[MAXN], inv[MAXN], finv[MAXN];
ull modmul(ull a, ull b, ull M) {
    int ret = a * b - mod * ull(1.L / mod * a * b);
    return ret + mod * (ret < 0) - mod * (ret >= (int)mod);
}
ull power(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}
ull power(ull b, ull e) {
    ull ans = 1;
    for (; e; b *= b, e /= 2)
        if (e & 1) ans *= b;
    return ans;
}
void init(int n) {
    fac[0] = fac[1] = 1;
    inv[0] = inv[1] = 1;
    finv[0] = finv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fac[i] = (fac[i - 1] * i) % MOD;
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        finv[i] = (finv[i - 1] * inv[i]) % MOD;
    }
}
ull nCr(ull x, ull y) {
    if (x < 0 || y > x) {
        return 0;
    }
    return (fac[x] * ((finv[y] * finv[x - y]) % MOD)) % MOD;
}

ull Inv(int x) {
    return power(x, MOD - 2, MOD);
}
};
using namespace combinations;
