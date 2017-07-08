// https://open.kattis.com/problems/classrooms
// bykrist7599555
#include <bits/extc++.h>
#include <iostream>
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using namespace std;
typedef std::pair<int,int> pii;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    uint n, room;
    cin >> n >> room;
    vector<pii> in(n);
    loop(i,n){
        cin >> in[i].fi >> in[i].se;
    }
    std::sort (all(in), [](const pii& a, const pii& b){ return a.se < b.se; });
    std::set <pii, std::greater<pii>> used; // time, id
    int ans = 0;
    for (pii p : in){
        auto it = used.upper_bound(pii(p.fi, -1));
        if (it != used.end()){
            used.erase(it);
            used.insert(pii(p.se,ans++));
        }else if (used.size() < room){
            used.insert(pii(p.se,ans++));
        }
    }
    cout << ans;
}
