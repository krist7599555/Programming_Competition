// https://open.kattis.com/problems/classrooms
// by krist7599555
// +segtree optimize get 1st place :)

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(auto i=(k);i!=(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
#define fi first
#define se second
using namespace std;
using namespace __gnu_pbds;
typedef std::pair<int,int> pii;

const int n = 1 << 18;
int room;
int sz = 0;
int seg[n * 2];
int en [n], *p = en;

inline int find_less_than_equal_idx (int x){
    if (x == -1) return -1;
    x += n;
    while (!seg[x] and x & x-1){
        x = (x-1) >> 1;
    }
    if(!(x & x-1) and !seg[x]) return -1;
    while (x < n){
        x <<= 1;
        if (seg[x|1]) x |= 1;
    }
    return x - n;
}
inline void update_idx (int x, int v){
    seg[x+=n] += v;
    while (x != 1){
        seg[x>>=1] += v;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _n;
    cin >> _n >> room;
    vector<pii> in(_n);
    loop(i,_n){
        cin >> in[i].fi >> in[i].se;
        in[i].se++; // [,)
    }
    std::sort (all(in), [](const pii& a, const pii& b){ return a.se < b.se; });
    for (pii& i : in){ // unique and copy with out sort again
        if (p == en or p[-1] != i.se){
            *p++ = i.se;
    }}
    p = std::unique (en, p);
    
    int* r = en; // optimize bound
    int ans = 0;

    for (pii& i : in){
        int s = i.fi;
        int t = i.se;
        while (*r != t) ++r;
        int x = find_less_than_equal_idx (std::upper_bound (en, r, s) - en - 1);
        if (x != -1){
            update_idx(x, -1);
            update_idx(r - en, 1);
            ans++;
        }else if (seg[1] < room){
            update_idx(r - en, 1);
            ans++;
        }
    }
    cout << ans;
}
