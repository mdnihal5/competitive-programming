struct MergeSortTree {
    int n;
    vector<vector<int>> t;

    MergeSortTree(const vector<int> &a) : n(a.size()), t(4 * n) { build(a, 1, 0, n - 1); }

    void build(const vector<int> &a, int p, int l, int r) {
        if (l == r) { t[p] = {a[l]}; return; }
        int m = (l + r) / 2;
        build(a, 2 * p, l, m);
        build(a, 2 * p + 1, m + 1, r);
        merge(all(t[2 * p]), all(t[2 * p + 1]), back_inserter(t[p]));
    }

    template<typename G>
    void visit(int p, int l, int r, int ql, int qr, G &g) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) return g(t[p]);
        int m = (l + r) / 2;
        visit(2 * p, l, m, ql, qr, g);
        visit(2 * p + 1, m + 1, r, ql, qr, g);
    }

    int countLess(int l, int r, int x) {
        int res = 0;
        auto g = [&](vector<int> &v) { res += lower_bound(all(v), x) - v.begin(); };
        visit(1, 0, n - 1, l, r, g);
        return res;
    }

    int predecessor(int l, int r, int x) {
        int res = -inf;
        auto g = [&](vector<int> &v) {
            auto it = upper_bound(all(v), x);
            if (it != v.begin()) res = max(res, *prev(it));
        };
        visit(1, 0, n - 1, l, r, g);
        return res;
    }

    int successor(int l, int r, int x) {
        int res = inf;
        auto g = [&](vector<int> &v) {
            auto it = lower_bound(all(v), x);
            if (it != v.end()) res = min(res, *it);
        };
        visit(1, 0, n - 1, l, r, g);
        return res;
    }
};
