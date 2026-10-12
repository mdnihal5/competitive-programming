namespace NTT {
constexpr int MOD = 998244353, ROOT = 3;

int power(int a, int e) {
    int r = 1;
    for (; e; e >>= 1, a = a * a % MOD) if (e & 1) r = r * a % MOD;
    return r;
}

void ntt(vector<int> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int w = power(ROOT, (MOD - 1) / len);
        if (invert) w = power(w, MOD - 2);
        for (int i = 0; i < n; i += len) {
            int wn = 1;
            for (int j = 0; j < len / 2; j++, wn = wn * w % MOD) {
                int u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u >= v ? u - v : u - v + MOD;
            }
        }
    }
    if (invert) {
        int nInv = power(n, MOD - 2);
        for (int &x : a) x = x * nInv % MOD;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};
    int size = a.size() + b.size() - 1, n = 1;
    while (n < size) n <<= 1;
    a.resize(n), b.resize(n);
    ntt(a, false), ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(size);
    return a;
}
}
