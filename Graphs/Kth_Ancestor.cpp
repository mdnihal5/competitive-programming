class TreeAncestor {
public:
    vector<vector<int> > p;
    TreeAncestor(int n, vector<int>& parent) {
        p.resize(n+1,vector<int>(20,-1));
        for(int i=0;i<n;i++)
        {
            p[i][0]=parent[i];
        }
        for(int i=1;i<20;i++)
        {
            for(int j=1;j<n;j++)
            {
                if(p[j][i-1]!=-1)p[j][i]=p[p[j][i-1]][i-1];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for(int i=0;i<20;i++)
        {
            if(k&(1<<i))node=p[node][i];
            if(node==-1)return -1;
        }
        return node;
    }
};
