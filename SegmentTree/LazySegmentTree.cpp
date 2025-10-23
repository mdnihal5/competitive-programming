#define ll long long
#define pb push_back

class SegTree {
public:
    SegTree(int n): n(n), mn(4*n, 0), mx(4*n, 0), lz(4*n, 0) {}
    
    void add(int l, int r, int v) {
        if(l <= r) add(l, r, v, 1, 0, n-1);
    }
    
    int get(int pos) {
        return get(pos, 1, 0, n-1);
    }

    int firstEq(int T, int Rmax) {
        return firstEq(T, Rmax, 1, 0, n-1);
    }

private:
    int n;
    std::vector<int> mn, mx, lz;
    
    void apply(int idx,int v){
        mn[idx]+=v;
        mx[idx]+=v;
        lz[idx]+=v;
    }
    
    void push(int idx){
        if(lz[idx]){
            apply(idx<<1,lz[idx]);
            apply(idx<<1|1,lz[idx]);
            lz[idx]=0;
        }
    }
    
    void add(int l, int r, int v, int idx, int L, int R) {
        if(l > R || r < L || l > r) return;
        if(l <= L && R <= r) {
            apply(idx, v);
            return;
        }
        push(idx);
        
        int M = (L + R)>>1;
        add(l, r, v, idx<<1, L, M);
        add(l, r, v, idx<<1|1, M+1, R);
        mn[idx] = min(mn[idx<<1], mn[idx<<1|1]);
        mx[idx] = max(mx[idx<<1], mx[idx<<1|1]);
    }

    int get(int pos, int idx, int L, int R) {
        if(L == R) return mn[idx];
        push(idx);
        int M = (L+R)>>1;

        if(pos <= M) return get(pos, idx<<1, L, M);
        else return get(pos, idx<<1|1, M+1, R);
    }
    
    int firstEq(int T, int Rmax, int idx, int L, int R) {
        if(Rmax < 0 || L > Rmax) return -1;
        if(T < mn[idx] || T > mx[idx]) return -1;
        if(L == R) return L;

        push(idx);
        int M = (L+R)>>1;
        int left = firstEq(T, Rmax, idx<<1, L, M);

        if(left != -1) return left;
        return firstEq(T, Rmax, idx<<1|1, M+1, R);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        
        SegTree st(n);
        vector<int> last(100001, -1);

        for(int r = 0; r < n; r++) {
            int x = nums[r];
            int s = ((x & 1) == 0) ? 1 : -1;
            int p = last[x];

            if(p != -1) st.add(p, n-1, -s);
            st.add(r, n-1, s);

            int T = st.get(r);
            if(T == 0) ans = max(ans, r+1);
            
            int i = st.firstEq(T, r-1);
            if(i != -1) ans = max(ans, r - i);
            last[x] = r;
        }

        return ans;
    }
};
