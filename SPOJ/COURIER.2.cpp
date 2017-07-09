// spoj : COURIER
// by krist7599555
// floyd's algorithm + travelling salesman bitmask

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
typedef std::vector<Vec> VVec;
const int mxn = 110;
const int inf = 1e9;
const int mlg = 12;

int fff[mxn][mxn];

bool vi[1<<mlg][13];
int  dp[1<<mlg][13];

int solve (int msk, int nw, const VVec& table){
	if (vi[msk][nw]) return dp[msk][nw];
	if (!msk) return table[nw].back();
	int res = inf;
	loop(i,mlg){
		if (msk & 1 << i)
			res = std::min(res, solve(msk ^ 1 << i, i, table) + table[nw][i]);
	}
	vi[msk][nw] = true;
	return dp[msk][nw] = res;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tcase; 
	cin >> tcase;
	loop(_,tcase){
		int n, m, s;
		cin >> n >> m >> s;
		std::fill_n (*fff, mxn * mxn, inf);
		std::fill_n (*vi, sizeof(vi), false);
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
		v.emplace_back(s,s);
		int sz = v.size();
		vector<Vec> dist(sz,Vec(sz));
		loop(i,sz){
		loop(j,sz){
			dist[i][j] = fff[v[i].se][v[j].fi];
		}}
		cout << solve((1<<(sz-1))-1, sz-1, dist) + real_cost << '\n';
	}
}
