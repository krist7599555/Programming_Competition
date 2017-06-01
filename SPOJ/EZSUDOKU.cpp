// spoj : EZSUDOKU
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
#include <cstring>
#define foo(i,k,n) for(int i=(k);i<=int(n);++i)
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define all(x) x.begin(),x.end()
using namespace std;
typedef std::pair<int,int> pii;
typedef std::vector<pii>::iterator It;
 
#define bit(x) (1 << (x))
#define quat(i,j,k) (bq[(i)/4*2 + (j)/4])[k]
#define empt(i,j,k) not ((br[i] & bit(k)) or (bc[j] & bit(k)) or quat(i,j,k) == 0)
#define sett(i,j,k,v) br[i] ^= bit(k), bc[j] ^= bit(k), dp[i][j] ^= k, quat(i,j,k) -= v
 
int bq[4][8],br[8],bc[8];
int dp[8][8];
 
bool recur (It s, It t){
	if (s == t) return true;
	int i = s->first;
	int j = s->second;
	rep(k,0,8){
		if (empt(i,j,k)){
			sett(i,j,k,1);
			if (recur(s+1,t)) 
				return true;
			sett(i,j,k,-1);
	}}
	return false;
}
 
int main(){
 
	cin.sync_with_stdio(0);
	
	int tes; cin >> tes;
	foo(t,1,tes){
		printf("Test case #%d: ", t);
		
		std::fill_n (*dp, 8 * 8, 0);
		std::fill_n (*bq, 4 * 8, 2);
		std::fill_n (br, 8, 0);
		std::fill_n (bc, 8, 0);
		
		bool input_check = true;
		std::vector<pii> blank;
		rep(i,0,8){
		rep(j,0,8){
			int val;
			cin >> val;
			if (--val != -1){
				if (empt(i,j,val)) 
					sett(i,j,val,1);
				else input_check = false;
			}else blank.emplace_back(i,j);
		}}
		
		if (input_check and recur (all(blank))){
			puts("YES");
			rep(i,0,8){
			rep(j,0,8){
				printf("%d%c",dp[i][j]+1," \n"[j==7]);
			}}
		}else puts("NO");
	}
}
