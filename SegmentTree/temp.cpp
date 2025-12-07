struct SegmentTree {
private:
    int n;
    vector<vector<int>> tree;
    vector<int> arr;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = {arr[l]};
        } else {
            int m = (l + r) / 2;
            build(2*node+1, l, m);
            build(2*node+2, m+1, r);
            tree[node].resize(tree[2*node+1].size() + tree[2*node+2].size());
            merge(tree[2*node+1].begin(), tree[2*node+1].end(), tree[2*node+2].begin(), tree[2*node+2].end(), tree[node].begin());
        }
    }

    int query(int node, int l, int r, int ql, int qr, int x) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) 
            return tree[node].end() - lower_bound(tree[node].begin(), tree[node].end(), x);
        int m = (l + r) / 2;
        return query(2*node+1, l, m, ql, qr, x) + query(2*node+2, m+1, r, ql, qr, x);
    }

    void update(int node, int l, int r, int idx, int oldVal, int newVal) {
        auto it = lower_bound(tree[node].begin(), tree[node].end(), oldVal);
        *it = newVal;  
        sort(tree[node].begin(), tree[node].end());
        if (l != r) {
            int m = (l + r) / 2;
            if (idx <= m) update(2*node+1, l, m, idx, oldVal, newVal);
            else update(2*node+2, m+1, r, idx, oldVal, newVal);
        }
    }

public:
    SegmentTree(vector<int>& a) {
        n = a.size();
        arr = a;
        tree.resize(4*n);
        build(0, 0, n-1);
    }

    int query(int l, int r, int x) { return query(0, 0, n-1, l, r, x); }

    void set(int idx, int val) {
        update(0, 0, n-1, idx, arr[idx], val);
        arr[idx] = val;
    }

    int get(int idx) { return arr[idx]; }
};
