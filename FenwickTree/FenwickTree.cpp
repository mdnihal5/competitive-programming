#include<bits/stdc++.h>
using namespace std;
class FenwickTree {
    vector<int>tree;
    int size;
    public:
    FenwickTree(int n): tree(n + 1, 0), size(n) {};
    void update(int idx, int add) {
        for (++idx; idx <= size; idx += idx & -idx) {
            tree[idx] += add;
        }
    }
    int query(int idx) {
        int sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }
    int sum(int l, int r) {
        return query(r) - query(l - 1);
    }
    int lower_bound(int val)
    {
        int ind = 0, sum = 0;
        for (int i = 20; i >= 0; i--)
        {
            if ( ind+(1<<i)<=size && tree[ind + (1 << i)] + sum < val)
            {
                ind += (1 << i);
                sum += tree[ind];
            }
        }
        return ind + 1;
    }
};
int main()
{
    int T=1; cin>>T;
    while(T--){
        int n; cin>>n;
        FenwickTree Tree(n+1);
        for(int i=1;i<=n;i++){
            int  x; cin>>x;
            Tree.update(i,x);
        }
        for(int i=1;i<=n;i++){
            cout<<Tree.sum(i,i)<<" ";
        }
    }
}
