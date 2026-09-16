// Author : md_nihal
//
// This mirrors the live `normal` UltiSnips snippet exactly (cpp.snippets resolves
// the debug.hpp include path via python interpolation to this repo's clone location;
// here it's a plain relative include since this file already lives beside debug.hpp).

#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n" // remove this for interactive problems
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#ifndef DEBUG
#define debug(x...);
#else
#include "debug.hpp"
#endif

/*=========================================== SOLUTION ===========================================*/

void ____solve() {

}

/*============================================= MAIN =============================================*/

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int Test = 1;  cin >> Test;

    for (int Case = 1; Case <= Test; Case++) {
        debug(Case);
        ____solve();
    }
}
