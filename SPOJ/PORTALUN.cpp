// spoj : PORTALUN
// by krist7599555
// game theory grundy number on num game 
// mex (minimum exclusive set)

#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define sz(x) int((x).size())
#define fi first
#define se second
using namespace std;
typedef long long lli;
typedef std::pair<int,int> pii;
typedef std::vector<int> Vec;
typedef std::string Str;
 
constexpr int mxn = 1000;
int grund[mxn]; // grundy number
Vec dag  [mxn];
 
int main(){
	cin.sync_with_stdio(0);
	int n, m;
	while (cin >> n >> m){
		std::for_each(dag, dag + n, mem_fn(&Vec::clear));
		loop(_,m){
			int u = input() - 1;
			int v = input() - 1;
			tie(u, v) = pii(std::minmax(u,v));
			if (u != v){
				dag[v].push_back(u);
		}}
		rep(i,0,n){
			std::transform(all(dag[i]), dag[i].begin(), [=](int i){ return grund[i]; });
			std::sort(all(dag[i]));
			dag[i].erase(std::unique(all(dag[i])), dag[i].end());
			int mex = 0;
			while (mex != sz(dag[i]) and dag[i][mex] == mex) ++mex;
			grund[i] = mex;
		}
		int sm = 0;
		loop(_,input()){
			sm ^= grund[input() - 1];
		}
		puts(sm ? "I win": "I lose");
	}
}
