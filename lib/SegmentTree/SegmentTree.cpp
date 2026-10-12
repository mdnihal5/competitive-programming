template<typename T, typename F>
struct SegTree {
    int n;
    vector<T> t;
    T id;
    F combine;

    SegTree(const vector<T> &a, T id, F combine) : n(a.size()), t(2 * n, id), id(id), combine(combine) {
        for (int i = 0; i < n; i++) t[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = combine(t[2 * i], t[2 * i + 1]);
    }

    void update(int i, T val) {
        for (t[i += n] = val; i > 1; i >>= 1) t[i >> 1] = combine(t[i & ~1], t[i | 1]);
    }

    T query(int l, int r) {
        T resl = id, resr = id;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = combine(resl, t[l++]);
            if (r & 1) resr = combine(t[--r], resr);
        }
        return combine(resl, resr);
    }
};
