class Solution {
public:
    static const int N = 1e5 + 5;
    static const int INF = 1e9;

    int nxt[N];
    struct Seg {
        struct Node {
            int l, r;
            int mn, mx;
            int lazy;
        };
        vector<Node> t;
        Seg(int n): t(4*n+5) { build(1,1,n); }
    
        void build(int p,int l,int r){
            t[p] = {l,r,0,0,0};
            if(l==r) return;
            int m=(l+r)>>1;
            build(p<<1,l,m);
            build(p<<1|1,m+1,r);
        }
        void apply(int p,int v){
            t[p].mn+=v; t[p].mx+=v; t[p].lazy+=v;
        }
        void push(int p){
            if(t[p].lazy){
                apply(p<<1,t[p].lazy);
                apply(p<<1|1,t[p].lazy);
                t[p].lazy=0;
            }
        }
        void pull(int p){
            t[p].mn=min(t[p<<1].mn,t[p<<1|1].mn);
            t[p].mx=max(t[p<<1].mx,t[p<<1|1].mx);
        }
        void range_add(int p,int L,int R,int v){
            auto [l,r,_,__,___]=t[p];
            if(R<l||r<L) return;
            if(L<=l && r<=R){ apply(p,v); return; }
            push(p);
            range_add(p<<1,L,R,v);
            range_add(p<<1|1,L,R,v);
            pull(p);
        }
        int findrightval(int p,int val){
            auto &nd=t[p];
            if(nd.mn>val || nd.mx<val) return -1;
            if(nd.l==nd.r) return (nd.mn==val? nd.l : -1);
            push(p);
            int res = findrightval(p<<1|1, val);
            if(res!=-1) return res;
            return findrightval(p<<1, val);
        }
    };
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;
        unordered_map<int, int>vis;
        Seg seg(n);
        for (int i = n - 1; i >= 0; --i) {
            int x = nums[i];
            auto it = vis.find(x);
            nxt[i+1] = (it==vis.end() ? 0 : it->second);
            vis[x] = i+1;
        }
        unordered_set<int> seen; seen.reserve(n*2);
        for (int i = 1; i <= n; ++i) {
            int x = nums[i-1];
            if (seen.insert(x).second) {
                int s = (x&1) ? +1 : -1;
                seg.range_add(1, i, n, s);
            }
        }
        int ans = 0;
        for (int L = 1; L <= n; ++L) {
            int R0 = seg.findrightval(1, 0);
            if (R0 != -1 && R0 >= L) {
                ans = max(ans, R0 - L + 1);
            }
            int x = nums[L-1];
            int s = (x&1) ? +1 : -1;
            int endR = (nxt[L]==0 ? n : nxt[L]-1);
            if (L <= endR) seg.range_add(1, L, endR, -s);
            seg.range_add(1, L, L, INF);
        }
        return ans;
    }
};
