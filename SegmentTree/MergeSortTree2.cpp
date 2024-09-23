class SegmentTree {
public:
    SegmentTree(const vector<int>& a) {
        n = a.size();
        t.resize(4 * n);
        build(a, 1, 0, n - 1);
        this->a = a;
    }
    int queryL(int l, int r, int x) {
        return queryL(1, 0, n - 1, l, r, x);
    }
    int queryR(int l, int r, int x) {
        return queryR(1, 0, n - 1, l, r, x);
    }
    void update(int pos, int new_val) {
        update(1, 0, n - 1, pos, new_val);
    }
private:
    vector<vector<int>> t;
    vector<int> a; 
    int n;
    void build(const vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            merge(t[v * 2].begin(), t[v * 2].end(),
                  t[v * 2 + 1].begin(), t[v * 2 + 1].end(),
                  back_inserter(t[v]));
        }
    }

    int queryR(int v, int tl, int tr, int l, int r, int x) {
        if (l > r) return INT_MAX;
        if (l == tl && r == tr) {
            auto pos = lower_bound(t[v].begin(), t[v].end(), x);
            return (pos != t[v].end()) ? *pos : INT_MAX;
        }
        int tm = (tl + tr) / 2;
        return min(queryR(v * 2, tl, tm, l, min(r, tm), x),
                   queryR(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x));
    }

    int queryL(int v, int tl, int tr, int l, int r, int x) {
        if (l > r) return INT_MIN;
        if (l == tl && r == tr) {
            auto pos = upper_bound(t[v].begin(), t[v].end(), x);
            return (pos != t[v].begin()) ? *(--pos) : INT_MIN;
        }
        int tm = (tl + tr) / 2;
        return max(queryL(v * 2, tl, tm, l, min(r, tm), x),
                   queryL(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        auto it = find(t[v].begin(), t[v].end(), a[pos]);
        if (it != t[v].end()) {
            t[v].erase(it);
            t[v].insert(lower_bound(t[v].begin(), t[v].end(), new_val), new_val);
        }
        if (tl != tr) {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(v * 2, tl, tm, pos, new_val);
            } else {
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            }
        } else {
            a[pos] = new_val; 
        }
    }
};
