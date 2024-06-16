template<typename T>
class LazySegmentTree {
private:
    vector<T> tree, lazy;
    vector<T> nums;
    int n;
    T identity;
 
    bool isValid(int idx) {
        return idx >= 0 && idx < n;
    }
 
    T combine(T left, T right) {
        return left + right; // Change this for different operations
    }
 
    void apply(T &a, T b, int length) {
        a += b * length; // Change this for different operations
    }
 
    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = start + (end - start) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
        }
    }
 
    void push(int node, int start, int end) {
        if (lazy[node] != identity) {
            apply(tree[node], lazy[node], end - start + 1);
            if (start != end) {
                lazy[2 * node] = combine(lazy[2 * node], lazy[node]);
                lazy[2 * node + 1] = combine(lazy[2 * node + 1], lazy[node]);
            }
            lazy[node] = identity;
        }
    }
 
    void updateRange(int node, int start, int end, int l, int r, T val) {
        push(node, start, end);
        if (r < start || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            lazy[node] = combine(lazy[node], val);
            push(node, start, end);
            return;
        }
        int mid = start + (end - start) / 2;
        updateRange(2 * node, start, mid, l, r, val);
        updateRange(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
 
    T queryRange(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || end < l) {
            return identity;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        T leftResult = queryRange(2 * node, start, mid, l, r);
        T rightResult = queryRange(2 * node + 1, mid + 1, end, l, r);
        return combine(leftResult, rightResult);
    }
 
public:
    LazySegmentTree(const vector<T>& nums, T identity) : nums(nums), identity(identity) {
        n = nums.size();
        tree.resize(4 * n, identity);
        lazy.resize(4 * n, identity);
        build(1, 0, n - 1);
    }
 
    LazySegmentTree(int size, T identity) : identity(identity) {
        n = size;
        nums.resize(n, identity);
        tree.resize(4 * n, identity);
        lazy.resize(4 * n, identity);
        build(1, 0, n - 1);
    }
 
    void updateRange(int l, int r, T val) {
        updateRange(1, 0, n - 1, l, r, val);
    }
 
    T queryRange(int l, int r) {
        return queryRange(1, 0, n - 1, l, r);
    }
};
