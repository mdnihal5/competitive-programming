bool marked[N];
int  sp[N];

void Sieve() {
    for (int i = 2; i < N; i += 2)    sp[i] = 2;//even numbers have smallest prime factor 2
    for (int i = 3; i < N; i += 2) {
        if (!marked[i]) {
            sp[i] = i;
            for (int j = i; (j * i) < N; j += 2) {
                if (!marked[j * i])    marked[j * i] = true, sp[j * i] = i;
            }
        }
    }
}


vector <int> factorize(int k) {
    vector <int> ans;
    while (k > 1) {
        ans.push_back(sp[k]);
        k /= sp[k];
    }
    return ans;
}
