struct Sieve {
    vector<int32_t> spf, primes;

    Sieve(int n) : spf(n + 1) {
        for (int i = 2; i <= n; i++) {
            if (!spf[i]) spf[i] = i, primes.push_back(i);
            for (int p : primes) {
                if (p > spf[i] || p * i > n) break;
                spf[p * i] = p;
            }
        }
    }

    bool isPrime(int x) const { return x >= 2 && spf[x] == x; }

    vector<int32_t> factorize(int x) const {
        vector<int32_t> f;
        for (; x > 1; x /= f.back()) f.push_back(spf[x]);
        return f;
    }
};
