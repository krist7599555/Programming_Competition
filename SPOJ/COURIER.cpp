// spoj : COURIER
// floyd's algorithm + optimize permutation
#include <bits/stdc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i<=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
#define fi first
#define se second
using namespace std;
typedef std::pair<int,int> pii;
typedef std::vector<int> Vec;

const int mxn = 110;
const int inf = 1e9;
int fff[mxn][mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tcase; 
	cin >> tcase;
	loop(_,tcase){
		int n, m, s;
		cin >> n >> m >> s;
		std::fill_n (*fff, mxn * mxn, inf);
		loop(_,m){
			int u,v,w;
			cin >> u >> v >> w;
			fff[u][v] = fff[v][u] = w;
		}
		rep(k,1,n){
		rep(i,1,n){
		rep(j,1,n){
			fff[i][j] = i == j ? 0 : std::min(fff[i][j], fff[i][k] + fff[k][j]);
		}}}
		int z;
		cin >> z;
		std::vector<pii> v;
		int real_cost = 0;
		loop(_,z){
			pii p;
			int t;
			cin >> p.fi >> p.se >> t;
			real_cost += fff[p.fi][p.se] * t;
			v.resize(sz(v)+t,p);
		}
		std::sort(all(v));
		int ans = inf;
		#define dist(pivot,pir) (fff[pivot][(pir).fi])
		do{
			int pv = s;
			int sm = 0;
			for (auto it = begin(v); it != end(v); ++it){
				while (sm + dist(pv,*it) >= ans){
					auto nx = std::find_if (it + 1, end(v), std::bind1st(std::less<pii>(), *it));
					if (nx != end(v)){
						std::iter_swap(it, nx);
						std::sort(it+1, end(v));
					}else goto out;
				}
				if (sm +  dist(pv,*it) < ans){
					sm += dist(pv,*it);
					pv = it->se;
				}else goto out;
			}
			ans = std::min(ans, sm + fff[pv][s]);
			out:;
		}while(next_permutation(all(v)));
		cout << ans + real_cost << '\n';
	}
}
