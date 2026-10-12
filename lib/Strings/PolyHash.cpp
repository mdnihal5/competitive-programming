struct PolyHash {
    static constexpr uint64_t MOD = (1ULL << 61) - 1;
    uint64_t base;
    vector<uint64_t> pw, pre;

    static uint64_t mulmod(uint64_t a, uint64_t b) {
        __uint128_t p = (__uint128_t)a * b;
        uint64_t r = (uint64_t)(p & MOD) + (uint64_t)(p >> 61);
        return r >= MOD ? r - MOD : r;
    }

    template<typename T>
    PolyHash(const vector<T> &a) : pw(a.size() + 1, 1), pre(a.size() + 1) {
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        base = rng() % (MOD - 256) + 256;
        for (int i = 0; i < (int)a.size(); i++) {
            int64_t v = (int64_t)a[i] % (int64_t)(MOD - 1);
            if (v < 0) v += MOD - 1;
            pw[i + 1] = mulmod(pw[i], base);
            pre[i + 1] = (mulmod(pre[i], base) + v + 1) % MOD;
        }
    }
    PolyHash(const string &s) : PolyHash(vector<int>(s.begin(), s.end())) {}

    uint64_t get(int l, int r) const {
        return (pre[r + 1] + MOD - mulmod(pw[r - l + 1], pre[l])) % MOD;
    }

    uint64_t combine(uint64_t leftHash, uint64_t rightHash, int rightLen) const {
        return (mulmod(leftHash, pw[rightLen]) + rightHash) % MOD;
    }
};
