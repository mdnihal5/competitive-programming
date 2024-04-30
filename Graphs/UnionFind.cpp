//based on rank
class UnionFind { 
    vector<int> root, rank;
public:
    UnionFind(int n) : root(n), rank(n) {
        rank.assign(n, 1);
        iota(root.begin(), root.end(), 0);
    }

    int Find(int x) {
        if (x == root[x])
            return x;
        else
            return root[x] = Find(root[x]);
    }

    void Union(int x, int y) {
        int rX = Find(x), rY = Find(y);
        if (rX == rY)
            return;
        if (rank[rX] > rank[rY])
            swap(rX, rY);
        root[rX] = rY;
        if (rank[rX] == rank[rY])
            rank[rY]++;
    }
    bool connected(int x, int y) { return Find(x) == Find(y); }
};

// based on size -> 
class DSU{
    std::vector<int>par,size;
    public:
    DSU(int n):par(n+5),size(n+5){
        for(int i=1;i<=n;i++) size[i]=1,par[i]=i;
    }
    int parent(int x){
        return (par[x]==x?x:parent(par[x]));   
    }
    void unite(int x,int y){
        int rootx=parent(x),rooty=parent(y);
        if(rootx==rooty) return;
        if(size[rootx]<size[rooty]) swap(rootx,rooty);
        par[rooty]=rootx;
        size[rootx]+=size[rooty];
    }
    bool connected(int x,int y){
        return parent(x)==parent(y);
    }
    int get_size(int x){
        return size[x];
    }
};

