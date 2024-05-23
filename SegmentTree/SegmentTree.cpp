class SegmentTree {
    vector<int>Tree;
    int n;
    int combine(int a, int b) {
        return min(a,b);
    }
    void build(const vector<int>&a, int v, int tl, int tr) {
        if ( tl > tr ) return;
        else if ( tl == tr ) {
            Tree[v] = a[tl];
        } else {
            int mid = (tl + tr) / 2;
            build(a, 2 * v, tl, mid);
            build(a, 2 * v + 1, mid + 1, tr);
            Tree[v] = combine(Tree[2 * v] , Tree[2 * v + 1]);
        }
    }
    void update(int v, int tl, int tr, int pos, int newval) {
        if ( tl > tr ) return;
        else if (tl == tr) {
            Tree[v] = newval;
        } else {
            int mid = (tl + tr) / 2;
            if ( pos <= mid ) {
                update(2 * v, tl, mid, pos, newval);
            } else update(2 * v + 1, mid + 1, tr, pos, newval);
            Tree[v] = combine( Tree[2 * v] , Tree[2 * v + 1]);
        }
    }
    int query(int v, int tl, int tr, int l, int r) {
        if ( l > r ) {
            return INT_MAX;
        }
        if (tl == l and tr == r) {
            return Tree[v];
        }
        int mid = (tl + tr) / 2;
        int left = query(2 * v, tl, mid, l, min(mid, r));
        int right = query(2 * v + 1, mid + 1, tr, max(mid + 1, l), r);
        return combine(left, right);
    }
public:
    SegmentTree(int size) {
        n = size;
        Tree.assign(4 * n, INT_MAX);
    }
    SegmentTree(const vector<int>&a) {
        n = a.size();
        Tree.assign(4 * n, 0);
        build(a, 1, 0, n - 1);
    }
    void update(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }
    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};




//

class SegmentTree {
    typedef int T;
    static constexpr T unit = INT_MAX;        //change this {INT_MAX,INT_MIN,0}
    T fun (T a, T b) { return min (a, b); } // (any associative fn)
    vector<T> s; int n;
  public:
    SegmentTree (int n = 0, T def = unit) : s (2 * n, def), n (n) {}
    void update (int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = fun (s[pos * 2], s[pos * 2 + 1]);
    }
    T query (int b, int e) { // query [b, e)
        T ra = unit, rb = unit;

        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = fun (ra, s[b++]);

            if (e % 2) rb = fun (s[--e], rb);
        }

        return fun (ra, rb);
    }
    T getfirst (int x, int l, int r) {
        if (query (l, r + 1) > x) return -1;

        int mid = -1;

        while (l <= r) {
            mid = (l + r) / 2;

            if (query (l, mid + 1) <= x) r = mid - 1;
            else l = mid + 1;
        }

        return l;
    }
};
