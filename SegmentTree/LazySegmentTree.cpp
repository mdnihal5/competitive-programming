class SegmentTree {
    struct Node {
        int mn = 0, mx = 0, sum = 0, lazy = 0;
        bool has_lazy = false;
    };
    int n;
    vector<Node> t;

    void apply(int p, int l, int r, int v) {
        t[p].mn += v;
        t[p].mx += v;
        t[p].sum += v * (r - l + 1);
        if (t[p].has_lazy) t[p].lazy += v;
        else { t[p].lazy = v; t[p].has_lazy = true; }
    }
    void push(int p, int l, int r) {
        if (!t[p].has_lazy || l == r) return;
        int m = (l + r) >> 1;
        apply(p<<1, l, m, t[p].lazy);
        apply(p<<1|1, m+1, r, t[p].lazy);
        t[p].lazy = 0;
        t[p].has_lazy = false;
    }
    void pull(int p) {
        t[p].mn = min(t[p<<1].mn, t[p<<1|1].mn);
        t[p].mx = max(t[p<<1].mx, t[p<<1|1].mx);
        t[p].sum = t[p<<1].sum + t[p<<1|1].sum;
    }
    void range_add(int p, int l, int r, int L, int R, int v) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) { apply(p, l, r, v); return; }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_add(p<<1, l, m, L, R, v);
        range_add(p<<1|1, m+1, r, L, R, v);
        pull(p);
    }
    Node query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return {INT_MAX, INT_MIN, 0, 0, false};
        if (L <= l && r <= R) return t[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        Node a = query(p<<1, l, m, L, R);
        Node b = query(p<<1|1, m+1, r, L, R);
        Node res;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        res.sum = a.sum + b.sum;
        return res;
    }
    int find_right_val(int p, int l, int r, int val) {
        if (t[p].mn > val || t[p].mx < val) return -1;
        if (l == r) return (t[p].mn == val ? l : -1);
        push(p, l, r);
        int m = (l + r) >> 1;
        int res = find_right_val(p<<1|1, m+1, r, val);
        if (res != -1) return res;
        return find_right_val(p<<1, l, m, val);
    }
public:
    SegmentTree(int n): n(n), t(4*n+5) {} // 1 based and [ L,R ]
    void Add(int L, int R, int v) { range_add(1, 1, n, L, R, v); }
    int Min(int L, int R) { return query(1, 1, n, L, R).mn; }
    int Max(int L, int R) { return query(1, 1, n, L, R).mx; }
    int Sum(int L, int R) { return query(1, 1, n, L, R).sum; }
    Node Query(int L, int R) { return query(1, 1, n, L, R); }
    int FindR(int val) { return find_right_val(1, 1, n, val); }
    void Set(int pos, int INF) { Add(pos, pos, INF); }
};

// SegmentTree st(n);
