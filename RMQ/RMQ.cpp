class SparseTable{
    vector<int> internalVector;
    vector<vector<int>> sparse;
    int n;
    bool valid = true;
    int logn;
    string typeF;
    void build(){
        for(int i=0;i<n;i++){
            sparse[i][0] = internalVector[i];
        }
        
        for(int j=1;j<=logn;j++){
            for(int i=0;i+(1<<j)-1<n;i++){
                if(typeF=="min"){
                    sparse[i][j] = min(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
                } else if(typeF=="max"){
                    sparse[i][j] = max(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
                } else if(typeF=="gcd"){
                    sparse[i][j] = __gcd(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
                } else if(typeF=="or"){
                    sparse[i][j] = sparse[i][j-1] | sparse[i+(1<<(j-1))][j-1];
                } else if(typeF=="and"){
                    sparse[i][j] = (sparse[i][j-1] & sparse[i+(1<<(j-1))][j-1]);
                }
            }
        }
    }
    
    public:
    
    SparseTable(vector<int> &v, string typeF) : typeF(typeF){
        
        n = v.size();
        if(n==0 || (typeF!="min" && typeF!="max" && typeF!="gcd" && typeF!="or" && typeF!="and")){
            valid = false;
            if(n==0){
                "please enter a valid vector";
            } else{
                cout<<"please enter a valid type"<<endl;
            }
        } else {
            logn = 31 - __builtin_clz(n);
            internalVector = v;
            sparse = vector<vector<int>>(n, vector<int>(logn+1, 0));
            build();
        }
    }
    
    int query(int l, int r){
        if(l>r || l<0 || r>=n){
            cout<<"please enter valid positions."<<endl;
            return -1;
        }
        if(!valid){
            cout<<"query not possible, table is not valid"<<endl;
            return -1;
        }
        int len = r-l+1;
        int loglen = 31 - __builtin_clz(len);
        if(typeF=="min"){
            return min(sparse[l][loglen], sparse[r-(1<<loglen)+1][loglen]);
        } else if(typeF=="max"){
            return max(sparse[l][loglen], sparse[r-(1<<loglen)+1][loglen]);
        } else if(typeF=="gcd"){
            return __gcd(sparse[l][loglen], sparse[r-(1<<loglen)+1][loglen]);
        } else if(typeF=="or"){
            return (sparse[l][loglen] | sparse[r-(1<<loglen)+1][loglen]);
        } else if(typeF=="and"){
            return (sparse[l][loglen] & sparse[r-(1<<loglen)+1][loglen]);
        }
    }
};
