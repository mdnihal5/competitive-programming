int fact[N];
int exp(int a, int b) {
    int ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = (ans * 1ll * a) % mod;
        b >>= 1;
        a = (a * 1ll * a) % mod;
    }
    return ans;
}
int nCr(int a, int b) {
    if (b > a or a == 0 or b == 0) return 1;
    return fact[a] * 1ll * exp(fact[b] * 1ll * fact[a - b] % mod, mod - 2) % mod;
}
