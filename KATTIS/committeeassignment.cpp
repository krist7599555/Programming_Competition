// https://open.kattis.com/problems/committeeassignment
// dynamic BFS on bitmask
#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
#define fi first
#define se second
using namespace std;
typedef std::vector<int> Vec;
typedef std::string Str;

//~ #define DEBUG
#define _ctz(x) ::__builtin_ctz(x) // count-trailing-zero


const int mxn = 15;
bool gr[1 << mxn]{}; // group == can formed group by this bitmask
int  dp[1 << mxn]{}; // bfs layer

int main(){
	ios::sync_with_stdio(0);
	uint _n, _m;
	while (cin >> _n >> _m,  _n | _m){
		if (!_m){
			cout << "1\n";
			continue;
		}
		uint id = 0;
		int bad[mxn]{};
		std::map<Str,int> mp;
		loop(_,_m){
			Str s1, s2;
			cin >> s1 >> s2;
			int v1 = mp.count(s1) ? mp[s1] : mp[s1] = id++;
			int v2 = mp.count(s2) ? mp[s2] : mp[s2] = id++;
			bad[v1] |= 1 << v2;
			bad[v2] |= 1 << v1;
		}
		
#ifdef DEBUG
		for (auto p : mp)
			cout << p.fi << ' ' << p.se << '\n';
#endif
		assert (id <= _n);
		assert (id == mp.size());
		
		const int n  = id;
		const int lm = 1 << n;
		
		rep(i,1,lm){
			dp[i] = true;
			rep(b,0,n){
				if ((1 << b & i) and (i & bad[b])){ //  b is in the group, but hate someone in group
					dp[i] = false;
					break;
			}}
			if (dp[i]){
				rep(b,0,n){
					if (1 << b & i)
					dp [1 << b ^ i] = false;
					// optimize if we try to used 1 << b ^ i, used i instance
					// believe that no any group can occupy
			}}
		}
		
		vector<Vec> group(n); // ordered by most significant bit
		rep(i,1,lm){
			if (dp[i]){
				for (int j = i; j != 0; j &= j-1){ // remove last-bit : j -= j & -j
					group[_ctz(j)].push_back(i);
#ifdef DEBUG
					cout << "group " << std::bitset<7>(i) << '\n';
#endif
				}
		}}
		
		std::queue<int> bfs; // still mask, need to remove it
		std::fill (dp, dp + lm, n+1); 
		bfs.emplace(lm-1); dp[lm-1] = 0;
		
		while (not bfs.empty()){
			int msk = bfs.front(); bfs.pop();
#ifdef DEBUG
			cout << std::bitset<7>(msk) << " : " << dp[msk] << '\n';
#endif
			if (msk == 0) continue;
			for (int nx : group[_ctz(msk)]){
				int nw_msk = msk & ~nx;
				if (dp[nw_msk] > dp[msk] + 1){
					dp[nw_msk] = dp[msk] + 1;
					bfs.emplace (nw_msk);
			}}
		}
		assert (1 <= dp[0] and dp[0] <= n);
		cout << dp[0] << '\n';
	}
}
