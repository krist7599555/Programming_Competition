// https://open.kattis.com/problems/committeeassignment
// dynamic BFS on bitmask
// give in, 4th place TT

#include <bits/stdc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define fi first
#define se second
using namespace std;
typedef std::vector<int> Vec;
typedef std::string Str;

#define _ctz(x) ::__builtin_ctz(x)

const int mxn = 15;
bool gr[1 << mxn]{}; 

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _n, _m;
    while (cin >> _n >> _m,  _n | _m){
        if (!_m){
            cout << "1\n";
            continue;
        }
        int id = 0;
        int bad[mxn]{};
        std::unordered_map<Str,int> mp;
        loop(_,_m){
            Str s1, s2;
            cin >> s1 >> s2;
            int v1 = mp.count(s1) ? mp[s1] : mp[s1] = id++;
            int v2 = mp.count(s2) ? mp[s2] : mp[s2] = id++;
            bad[v1] |= 1 << v2;
            bad[v2] |= 1 << v1;
        }
        
        const int n  = id;
        const int lm = 1 << n;
        
        rep(i,1,lm){
            gr[i] = true;
            rep(b,0,n){
                if ((i & 1 << b) and (i & bad[b])){ 
                    // b is member of i, but b hate some one in group i
                    gr[i] = false;
                    break;
            }}
            if (gr[i]){
                rep(b,0,n){
                    if (i & 1 << b)
                    gr [i ^ 1 << b] = false;    
                    // it is better to used group i instant of i ^ 1 << b
            }}
        }
        
        Vec group[n]{};
        for(int i = lm; --i;){
            if (gr[i]){
                group[_ctz(i)].push_back(i);    // people _ctz(i) can join group i
                gr[i & (i-1)] = true;           // can form group i - _ctz(i)
        }}
    
        std::fill (gr, gr + lm, false);
        Vec bfs(1, lm-1); gr[lm-1] = true;
         
        for (int t = 0; not bfs.empty(); ++t){
            Vec tmp;
            for (int msk : bfs){ // msk == people who not join any group
                if (msk == 0){
                    cout << t << '\n';
                    tmp.clear();
                    break;
                }else{
                    for (int nx : group[_ctz(msk)]){ // someof msk people can join group nx
                        int nw_msk = msk & ~nx;
                        if(!gr[nw_msk]){
                            gr[nw_msk] = true;
                            tmp.push_back(nw_msk);
                }}}
            }
            bfs.clear();
            bfs.swap(tmp);
            
        }// bfs
        
    }// test case
}// main
