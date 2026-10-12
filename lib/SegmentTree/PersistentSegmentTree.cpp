template<typename T, typename F>
struct PersistentSegTree {
    struct Node { T val; int l, r; };
    vector<Node> t;
    vector<int> roots;
    int n;
    T id;
    F combine;

    PersistentSegTree(const vector<T> &a, T id, F combine) : n(a.size()), id(id), combine(combine) {
        roots.push_back(build(a, 0, n - 1));
    }

    int add(T val, int l, int r) {
        t.push_back({val, l, r});
        return t.size() - 1;
    }

    int build(const vector<T> &a, int l, int r) {
        if (l == r) return add(a[l], -1, -1);
        int m = (l + r) / 2;
        int lc = build(a, l, m), rc = build(a, m + 1, r);
        return add(combine(t[lc].val, t[rc].val), lc, rc);
    }

    int update_(int p, int l, int r, int i, T val) {
        if (l == r) return add(val, -1, -1);
        int m = (l + r) / 2, lc = t[p].l, rc = t[p].r;
        if (i <= m) lc = update_(lc, l, m, i, val);
        else rc = update_(rc, m + 1, r, i, val);
        return add(combine(t[lc].val, t[rc].val), lc, rc);
    }

    int update(int version, int i, T val) {
        roots.push_back(update_(roots[version], 0, n - 1, i, val));
        return roots.size() - 1;
    }

    T query_(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return id;
        if (ql <= l && r <= qr) return t[p].val;
        int m = (l + r) / 2;
        return combine(query_(t[p].l, l, m, ql, qr), query_(t[p].r, m + 1, r, ql, qr));
    }

    T query(int version, int l, int r) { return query_(roots[version], 0, n - 1, l, r); }
};
