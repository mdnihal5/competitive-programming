struct Combinatorics {
    int n;
    vector<int> fac, inv, finv;

    Combinatorics(int n) : n(n), fac(n + 2), inv(n + 2), finv(n + 2) {
        fac[0] = inv[1] = finv[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
        for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;
        for (int i = 1; i <= n; i++) finv[i] = finv[i - 1] * inv[i] % mod;
    }

    int nCr(int a, int b) {
        if (b < 0 || b > a) return 0;
        return fac[a] * finv[b] % mod * finv[a - b] % mod;
    }

    int nPr(int a, int b) {
        if (b < 0 || b > a) return 0;
        return fac[a] * finv[a - b] % mod;
    }
};
