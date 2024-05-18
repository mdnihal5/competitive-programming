class SegmentTree {
  private:
    std::vector<int> tree;
    std::vector<int> lazy;
    int n, m;

    int combine(int left, int right) {
        // Modify this function based on your specific use case
        return (left + right);
    }

    void build(std::vector<int> &arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];

        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    void push(int v, int tl, int tr) {
        if (lazy[v] != 0) {
            tree[v] = (tr - tl + 1) * lazy[v]; // Modify this funcion based on your use case

            if (tl != tr) {
                lazy[v * 2] = lazy[v];
                lazy[v * 2 + 1] = lazy[v];
            }

            lazy[v] = 0;
        }
    }

    void update(int v, int tl, int tr, int l, int r, int x) {
        push(v, tl, tr);

        if (l > r) return;

        if (tl == l && tr == r) {
            lazy[v] = x;
            push(v, tl, tr);

        } else {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, std::min(r, tm), x);
            update(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, x);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);

        if (l > r) return 1;

        if (tl == l && tr == r) {
            return tree[v];
        }

        int tm = (tl + tr) / 2;
        return combine(query(v * 2, tl, tm, l, std::min(r, tm)),
                       query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
    }

  public:
    SegmentTree(std::vector<int> &arr, int mm) {
        n = arr.size();
        m = mm;
        tree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    void updateRange(int l, int r, int x) {
        update(1, 0, n - 1, l, r, x);
    }

    int queryRange(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
