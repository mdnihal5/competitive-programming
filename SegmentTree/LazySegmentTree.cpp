#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    struct Node {
        vector<int> sorted;  
        long long mn = LLONG_MAX, mx = LLONG_MIN, sum = 0, lazy = 0;
        bool has_lazy = false;
    };

    int n;
    vector<Node> t;

    void build(const vector<int>& arr, int p, int l, int r) {
        if (l == r) {
            t[p].sorted = {arr[l]};
            t[p].mn = t[p].mx = t[p].sum = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(arr, 2*p, l, m);
        build(arr, 2*p+1, m+1, r);
        t[p].sorted.resize(t[2*p].sorted.size() + t[2*p+1].sorted.size());
        merge(t[2*p].sorted.begin(), t[2*p].sorted.end(), t[2*p+1].sorted.begin(), t[2*p+1].sorted.end(), t[p].sorted.begin());
        t[p].mn = min(t[2*p].mn, t[2*p+1].mn);
        t[p].mx = max(t[2*p].mx, t[2*p+1].mx);
        t[p].sum = t[2*p].sum + t[2*p+1].sum;
    }

    void apply(int p, int l, int r, long long v) {
        t[p].mn += v;
        t[p].mx += v;
        t[p].sum += v * (r - l + 1);
        t[p].lazy += v;
        t[p].has_lazy = true;
    }

    void push(int p, int l, int r) {
        if (!t[p].has_lazy || l == r) return;
        int m = (l + r) / 2;
        apply(2*p, l, m, t[p].lazy);
        apply(2*p+1, m+1, r, t[p].lazy);
        t[p].lazy = 0;
        t[p].has_lazy = false;
    }

    void range_add(int p, int l, int r, int L, int R, long long v) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) { apply(p, l, r, v); return; }
        push(p, l, r);
        int m = (l + r) / 2;
        range_add(2*p, l, m, L, R, v);
        range_add(2*p+1, m+1, r, L, R, v);
        t[p].mn = min(t[2*p].mn, t[2*p+1].mn);
        t[p].mx = max(t[2*p].mx, t[2*p+1].mx);
        t[p].sum = t[2*p].sum + t[2*p+1].sum;
    }

    Node query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return { {}, LLONG_MAX, LLONG_MIN, 0, 0, false };
        if (L <= l && r <= R) return t[p];
        push(p, l, r);
        int m = (l + r) / 2;
        Node a = query(2*p, l, m, L, R);
        Node b = query(2*p+1, m+1, r, L, R);
        Node res;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        res.sum = a.sum + b.sum;
        res.sorted.resize(a.sorted.size() + b.sorted.size());
        merge(a.sorted.begin(), a.sorted.end(), b.sorted.begin(), b.sorted.end(), res.sorted.begin());
        return res;
    }

    int find_right_val(int p, int l, int r, int L, int R, int val) {
        if (R < l || r < L || t[p].mn > val || t[p].mx < val) return -1;
        if (l == r) return t[p].mn == val ? l : -1;
        push(p, l, r);
        int m = (l + r) / 2;
        int res = find_right_val(2*p+1, m+1, r, L, R, val);
        if (res != -1) return res;
        return find_right_val(2*p, l, m, L, R, val);
    }

public:
    SegmentTree(const vector<int>& arr) : n(arr.size()) { t.resize(4*n); build(arr, 1, 0, n-1); }

    void Add(int L, int R, long long v) { range_add(1, 0, n-1, L, R, v); }
    long long Min(int L, int R) { return query(1, 0, n-1, L, R).mn; }
    long long Max(int L, int R) { return query(1, 0, n-1, L, R).mx; }
    long long Sum(int L, int R) { return query(1, 0, n-1, L, R).sum; }
    int CountGE(int L, int R, int x) {
        Node res = query(1, 0, n-1, L, R);
        return res.sorted.end() - lower_bound(res.sorted.begin(), res.sorted.end(), x);
    }
    int FindR(int L, int R, int val) { return find_right_val(1, 0, n-1, L, R, val); }
};
