struct Node {
    long long val[2][2];
    Node() { val[0][0] = val[0][1] = val[1][0] = val[1][1] = 0; }
    Node(long long v): Node() { val[1][1] = v; }
    friend Node merge(Node l, Node r) {
        Node res;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                res.val[i][j] = max({l.val[i][0] + r.val[0][j], l.val[i][1] + r.val[0][j] , l.val[i][0] + r.val[1][j]});
            }
        }
        return res;
    }
    void update(long long v) { *this = Node(v); }
    long long answer() { return max({val[0][0], val[0][1], val[1][0], val[1][1]}); }
};

struct SegmentTree {
    int n;
    vector<Node> seg;
    SegmentTree(int n): n(n), seg(2 * n) {}
    template <typename Type>
    SegmentTree(vector<Type> a) {
        n = a.size();
        seg.resize(2 * n);
        for (int i = 0; i < n; i++) seg[i + n] = Node(a[i]);
        for (int i = n - 1; i > 0; i--) seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
    }
    void update(int i, long long v) {
        for (seg[i += n].update(v); i >>= 1; ) seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
    }
    Node query(int l, int r) {
        Node resl, resr;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = merge(resl, seg[l++]);
            if (r & 1) resr = merge(seg[--r], resr);
        }
        return merge(resl, resr);
    }
};

class Solution {
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), ans = 0, mod = 1e9 + 7;
        SegmentTree sg(nums);
        
        for (auto q : queries) {
            int i = q[0], x = q[1];
            sg.update(i, x);
            ans = (ans + sg.query(0, n - 1).answer()) % mod;
        }
        
        return ans;
    }
};
