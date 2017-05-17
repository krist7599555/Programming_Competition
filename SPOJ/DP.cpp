// spoj : DP
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
#define ALL(x) (x).begin(),(x).end()
#define fi first
#define se second
#define cin() ({int _; cin >> _; _;})
using namespace std;
typedef std::vector<int> Vec;
typedef std::pair<int,int> pii;
typedef std::pair<int,pii> Data;

const int mxn = 60;

Vec get_subset (){ // return list of distance from X to $
	
	static int r,c;
	static pii init;
	static int  dp[mxn][mxn];
	static char in[mxn][mxn];
	static bool vi[mxn][mxn];
	static const vector<pii> dir {{1,0},{0,1},{-1,0},{0,-1}};
	static std::priority_queue <Data,vector<Data>,greater<Data>> PQ;	
	
	cin >> r >> c;
	rep(i,0,r){ 
		cin >> in[i];
		rep(j,0,c){
			if (in[i][j] == 'X') init = {i,j};
	}}
	
	fill_n (vi[0], mxn * mxn, false);
	dp[init.fi][init.se] = 0;
	vi[init.fi][init.se] = true;
	PQ.push({0,init});
	
	while (not PQ.empty()){ // dijktra
		
		int v; pii p;
		tie(v,p) = PQ.top(); PQ.pop();
		if (v != dp[p.fi][p.se]) continue;
		
		for (pii d : dir){
			int i = p.fi + d.fi;
			int j = p.se + d.se;
			if (-1 < i and i < r and -1 < j and j < c){
				
				bool building = false;
				for (char c1 : "X$"){
				for (char c2 : {in[p.fi][p.se], in[i][j]}){
					if (c1 == c2) building = true;
				}}
				int nw_v = 0;
				if (not building){
					int diff = abs (in[i][j] - in[p.fi][p.se]);
					if (diff > 1) continue;
					else nw_v = v + (diff ? 3 : 1);
				}else 	 nw_v = v + 2;
				
				if (not vi[i][j] or dp[i][j] > nw_v){
					vi[i][j] = true;
					dp[i][j] = nw_v;
					PQ.push({nw_v,{i,j}});
				}
			}
		}
	}
	Vec res; // return list of distance
	rep(i,0,r){
	rep(j,0,c){
		if (in[i][j] == '$'){
			if (not vi[i][j]) return Vec(1,-1); // can not serve
			res.push_back (dp[i][j]);
	}}}
	return res;
}

int get_ans (Vec v){ // subsetsum int O(2^n) bitmask
	
	const int n    = v.size();
	const int pwn2 = 1 << n;
	const int lim  = pwn2 - 1;
	
	static int mx[1<<20];
	static int sm[1<<20];
	
	if (n <= 2) return accumulate (ALL(v),0);
	
	fill_n (mx, 1 << n, 0);
	fill_n (sm, 1 << n, 0);
	
	rep(i,0,n){
		mx[1<<i] = v[i];
		sm[1<<i] = v[i] + v[i];
	}
	rep(i,0,n){
	rep(m,0,pwn2){
		if (m & 1 << i){
			mx[m]  = max(mx[m],mx[m^1<<i]);
			sm[m] += sm[m^1<<i];
	}}}
	int res = 1e9;
	rep(i,0,pwn2){
		res = min (res, max(sm[i]-mx[i], sm[i^lim]-mx[i^lim]));
	}
	return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = cin();
    while (t--){
		cout << get_ans(get_subset()) << '\n';
	}
}

