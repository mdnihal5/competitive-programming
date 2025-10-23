struct Node{
    int mn, mx, ly;
};
struct segtree{
    int n; 
    vector<Node> st;
    segtree(int N=0){
        init(N);
    }
    void init(int N){
        n = N;
        st.assign(4*(n+5), {0,0,0});
    }
    void apply(int p, int val){
        st[p].mn += val;
        st[p].mx += val;
        st[p].ly += val;
    }
    void push(int p){
        if(st[p].ly != 0){
            apply(p<<1, st[p].ly);
            apply(p<<1|1, st[p].ly);
            st[p].ly = 0;
        }
    }
    void pull(int p){
        st[p].mn = min(st[p<<1].mn, st[p<<1|1].mn);
        st[p].mx = max(st[p<<1].mx, st[p<<1|1].mx);
    }
    void ra(int p, int l, int r, int L, int R, int val){
        if(R<l or r<L) return ;
        if(L<=l and r<=R){
            apply(p, val);
            return ;
        }
        push(p);
        int m = (l+r)>>1;
        ra(p<<1, l, m, L, R, val);
        ra(p<<1|1, m+1, r, L, R, val);
        pull(p);
    }
    void ra(int L, int R, int val){
        if(L>R) return ;
        ra(1, 0, n, L, R, val);
    }
    int pq(int p, int l, int r, int i){
        if(l==r) return st[p].mn;
        push(p);
        int m = (l+r)>>1;
        if(i<=m) return pq(p<<1, l, m, i);
        else return pq(p<<1|1, m+1, r, i);
    }
    int pq(int p){
        return pq(1, 0, n, p);
    }
    int fre(int p, int l, int r, int L, int R, int t){
        if(R<l or r<L) return -1;
        if(L<=l and r<=R){
            if(t<st[p].mn or t>st[p].mx) return -1;
            if(l==r) return l;
        }
        push(p);
        int m = (l+r)>>1;
        int res = fre(p<<1|1, m+1, r, L, R, t);
        if(res!=-1) return res;
        return fre(p<<1, l, m, L, R, t);
    }
    int fre(int L, int R, int t){
        if(L>R) return -1;
        return fre(1, 0, n, L, R, t);
    }
    
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> l;
        vector<int> p(n+1, 0);
        for(int i=1; i<=n; i++){
            if(l.count(nums[i-1])) p[i] = l[nums[i-1]];
            else p[i] = 0;
            l[nums[i-1]] = i;
        }
        vector<vector<int>> b(n+1);
        for(int i=1; i<=n; i++){
            b[p[i]].push_back(i);
        }
        segtree st(n);
        for(auto i:b[0]){
            int sg = (nums[i-1]%2) ? -1 : 1;
            st.ra(i, n, sg);
        }
        int ans = 0;
        for(int i=1; i<=n; i++){
            int t = st.pq(i-1);
            int r = st.fre(i, n, t);
            if(r!=-1) ans = max(ans, r-i+1);
            if(i<=n){
                for(auto j:b[i]){
                    int sg = (nums[j-1]%2) ? -1 : 1;
                    st.ra(j, n, sg);
                }
            }
        }
        return ans;
    }
};
