    vi preMex(n,-1),suffMex(n,-1);
    int mex=0; set<int>s;
    // prefix mex
    for(int i=0;i<n;i++){
        if(arr[i]>=mex)s.insert(arr[i]);
        while(s.size() and *s.begin()==mex) {
            mex++;
            s.erase(s.begin());
        }
        preMex[i]=mex;
    }
    // suffix mex
    s.clear(); mex=0;
    for(int i=n-1;i>=0;i--){
        if(arr[i]>=mex)s.insert(arr[i]);
        while(s.size() and *s.begin()==mex){
            mex++;
            s.erase(s.begin());
        }
        suffMex[i]=mex;
    }
