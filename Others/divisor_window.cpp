class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        int n=word.size(),ans=n/k-1;
        for(int i=k;2*i<=n;i++){
            if(n%i or i%k) continue; // remove i%k
            unordered_map<string,int>m;
            for(int j=0;j<n;j+=k){
                string sub=word.substr(j,k);
                m[sub]++;
            }
            for(auto &i:m){
                int x=n-i.first.size()*i.second;
                ans=min<int>(ans,x/i.first.size());
            }
        }
        return ans;
    }
};
