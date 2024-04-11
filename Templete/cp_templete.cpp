// Author : md_nihal

#include "bits/stdc++.h"
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2,fma")
#define Md_Nihal ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


typedef unsigned long long ull;
#define endl "\n"
#define int long long
#define i_64 int64_t
#define pi pair<int,int>
#define sz(a) (int)a.size()
#define vi vector<int>
#define vpi vector<pair<int,int>>
#define vs vector<string>
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define rep(x,n) for (int i = x; i <=(n); i++)
#define print(x) (x)?cout<<"YES\n":cout<<"NO\n";
const int mod = 1e9 + 7, inf = LONG_LONG_MAX, N = 1e6 + 7, MAX = 1e14 + 4;

template<class T, class V>istream& operator>>(istream &in, pair<T, V> &a) {in >> a.first >> a.second; return in;}
template<class T>istream& operator>>(istream &in, vector<T> &a) {for (auto &i : a) {in >> i;} return in;}
template<class T, class V>ostream& operator<<(ostream &os, pair<T, V> &a) {os << a.first << " " << a.second; return os;}
template<class T>ostream& operator<<(ostream &os, vector<T> &a) {for (auto &i : a) {os << i << " ";} return os;}

/*----------------------------------------------- PBDS --------------------------------------------*/

using namespace __gnu_pbds;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
template<class key, class value, class cmp = less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;

/*----------------------------------------------- PBDS ends --------------------------------------------*/

#ifndef ONLINE_JUDGE
#include "debug.hpp"
#else
#define debug(x...);
#endif

/*=========================================== SOLUTION ===========================================*/



void __solve(int testcases) {



}



/*============================================= MAIN =============================================*/

int32_t  main()
{
    Md_Nihal;
    int testcases = 1;    cin >> testcases;
    for (int i = 0; i < testcases; cout << endl) __solve(++i);
}
