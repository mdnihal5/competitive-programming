template<typename T>
class SegmentTree {
private:
    vector<T> tree;
    vector<T> nums;
    int n;
    T identity;
 
    bool isValid(int idx) {
        return idx >= 0 && idx < n;
    }
 
    T combine(T left, T right) {
        return left + right;
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
 
    void update(int node, int start, int end, int idx) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = start + (end - start) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx);
            } else {
                update(2 * node + 1, mid + 1, end, idx);
            }
            tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
        }
    }
 
    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return identity;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        T leftResult = query(2 * node, start, mid, l, r);
        T rightResult = query(2 * node + 1, mid + 1, end, l, r);
        return combine(leftResult, rightResult);
    }
 
public:
    SegmentTree(const vector<T>& nums, T identity) : nums(nums), identity(identity) {
        n = nums.size();
        tree.resize(4 * n, identity);
        build(1, 0, n - 1);
    }
    SegmentTree(int size, T identity) : identity(identity) {
        n = size;
        nums.resize(n, identity);
        tree.resize(4 * n, identity);
        build(1, 0, n - 1);
    }
    void update(int idx, T val) {
        nums[idx] = val;
        update(1, 0, n - 1, idx);
    }
 
    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
