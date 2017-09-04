#include <bits/stdc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i!=(n);++i)
using namespace std;
typedef long long lli;
typedef std::vector<int> Vec;
const int mxn = 5e5 + 10;

struct Data {
    char c;
    int  l, r;
};

lli cnt[mxn];
int deg[mxn];
Data in[mxn];
char ot[mxn];

int main(){
    cin.sync_with_stdio(0);
    int n;
    cin >> cnt[1] >> n;
    rep(i,1,n+1){
        Data& d = in[i];
        cin >> d.c >> d.l >> d.r;
        ot[i] = d.c;
        deg[d.l]++;
        deg[d.r]++;
    }
    std::queue<int> topo;
    rep(i,1,n+1){
        if (!deg[i]){
            topo.emplace(i);            
    }}
    while (!topo.empty()){
        int i = topo.front(); topo.pop();
        Data d = in[i];
        if (!--deg[d.l]) topo.emplace(d.l);
        if (!--deg[d.r]) topo.emplace(d.r);
        lli mn = cnt[i] / 2;
        lli mx = cnt[i] - mn;
        switch (d.c){
            case 'L' :  cnt[d.l] += mx;
                        cnt[d.r] += mn; break;
            case 'R' :  cnt[d.l] += mn;
                        cnt[d.r] += mx; break;
        }
        ot[i] = d.c ^ (cnt[i] & 1 ? 'L' ^ 'R' : '\0');
    }
    assert (cnt[0] == cnt[1]);
    puts (ot + 1);
}
