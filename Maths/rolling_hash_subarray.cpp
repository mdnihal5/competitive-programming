using ull = unsigned long long;

struct Hash {

    ull P = chrono::high_resolution_clock::now().time_since_epoch().count() ^ (ull)new char;
    vector<ull> h, p;

    Hash(const vector<int>& a) {

        int n = a.size();

        h.assign(n + 1, 0);
        p.assign(n + 1, 1);

        for(int i = 0; i < n; i++)
            p[i + 1] = p[i] * P,
            h[i + 1] = h[i] * P + a[i] + 1;
    }

    ull get(int l, int r) {

        return h[r + 1] - h[l] * p[r - l + 1];
    }
};
