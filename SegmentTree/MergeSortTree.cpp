//Author : MdNihal
// returns a value x x>=lv and x<=rv in range l to r 
// if you want to make r inclusive pass r+1 or make chages mentioned below


/*
for r inclusive{
    change s+1==e to s==e in build 
    and range should be (l,mid) and (mid+1,r) in build and get_ans
    if (s > r || e < l) {
        return -1;
    }
}

For count of elements
if (s > r || e < l) {
    return 0;
}
if (l <= s && e <= r) {
    return lower_bound(all(Tree[v]), rv) - lower_bound(all(Tree[v]), lv);
}
int mid = (s + e) / 2;
int x = get_ans(2 * v, s, mid, lv, rv, l, r);  // change this accordingly
int y = get_ans(2 * v + 1, mid , e, lv, rv, l, r);
return x + y; //change this accordingly

*/



class SegmentTree {
    int n;
    vector<vector<int>>Tree;
    void build(vector<int>&a, int v, int s, int e) {
        if (s + 1 == e) {
            Tree[v] = {a[s]};    // Base Case :
        } else {
            int mid = s + (e - s) / 2;
            build(a, 2 * v, s, mid);
            build(a, 2 * v + 1, mid, e);
            merge(all(Tree[2 * v]), all(Tree[2 * v + 1]), back_inserter(Tree[v])); // MergeFunction
        }
    }
    int get_ans(int v , int s, int e, int lv, int rv, int l , int r) {
        if (l <= s && e <= r) {
            auto best = lower_bound(all(Tree[v]), lv);
            if (best == Tree[v].end())
                return -1;
            else if (*best <= rv) {
                return *best;
            } else return -1;
        }
        if (s >= r || e <= l) {
            return -1;
        }
        int mid = (s + e) / 2;
        int x = get_ans(2 * v, s, mid, lv, rv, l, r);  // change this accordingly
        if (x != -1) return x;
        return get_ans(2 * v + 1, mid , e, lv, rv, l, r);  //change this accordingly
    }
public:
    SegmentTree(vector<int>&a) {
        n = a.size();
        Tree.resize(4 * n);
        build(a, 1, 0, n);
    }
    int query(int l, int r, int lv, int rv) {
        // returns a value x x>=lv and x<=rv in range l to r 
        // range [l,r)  : you can pass l,r+1 to include r
        return get_ans(1, 0, n, lv, rv, l, r);
    }
};
