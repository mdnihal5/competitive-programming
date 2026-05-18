
class RollingHash {
    using ll = long long;

    static constexpr ll mod1 = 1000000007;
    static constexpr ll mod2 = 1000000009;

    ll p1, p2;
    vector<ll> h1, h2, pw1, pw2;

public:
    RollingHash(const vector<int>& a) {
        int n = a.size();

        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();

        p1 = (seed % 900000000) + 100000000;
        p2 = ((seed ^ (seed << 1)) % 900000000) + 100000000;

        if (p1 % 2 == 0) p1++;
        if (p2 % 2 == 0) p2++;

        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        pw1.assign(n + 1, 1);
        pw2.assign(n + 1, 1);

        for (int i = 0; i < n; i++) {
            pw1[i + 1] = (pw1[i] * p1) % mod1;
            pw2[i + 1] = (pw2[i] * p2) % mod2;

            h1[i + 1] = (h1[i] * p1 + (a[i] + 1)) % mod1;
            h2[i + 1] = (h2[i] * p2 + (a[i] + 1)) % mod2;
        }
    }

    pair<ll,ll> get(int l, int r) {
        ll x1 = (h1[r + 1] - h1[l] * pw1[r - l + 1]) % mod1;
        ll x2 = (h2[r + 1] - h2[l] * pw2[r - l + 1]) % mod2;

        if (x1 < 0) x1 += mod1;
        if (x2 < 0) x2 += mod2;

        return {x1, x2};
    }
};
