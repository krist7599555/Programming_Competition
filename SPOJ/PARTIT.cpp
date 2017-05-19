// spoj : PARTIT
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
using namespace std;
typedef long long lli;
 
const int mxn  = 11;
const int mxv  = 220 + 10;
const int mxnv = 220 * 10 + 10;
 
 
inline lli f (int sz, int dig, int val){
	
	static lli  dp [mxn][mxv][mxnv];
	static bool cal[mxn][mxv][mxnv];	
	
	if (sz == 0 or dig < 0 or dig > mxv or sz < 1 or val < 0) return 0;
	if (cal[sz][dig][val]) return dp[sz][dig][val];
	
	if (sz == 1){
		return 	cal[sz][dig][val] = true,
			dp [sz][dig][val] = dig == val ? 1 : 0;
	}
	lli res = 0;
	for (int nx_dig = dig; dig + (sz-1) * nx_dig <= val; ++nx_dig){ // optimise
		res += f (sz-1, nx_dig, val - dig);
	}
	return 	cal[sz][dig][val] = true,
		dp [sz][dig][val] = res;
}
 
inline string print (int sz, int rem, lli k_th, int dig = 1){
	if (sz == 0){
		assert (k_th == 0);
		return "";	
	}
	lli qsum_way = 0;
	for (; dig <= mxv; ++dig){
		lli this_way = f (sz, dig, rem);
		if (k_th < qsum_way + this_way){
			return  std::to_string(dig) + ' ' +
				print (sz - 1, rem - dig, k_th - qsum_way, dig);
		}else qsum_way += this_way;
	}
	exit(1);
}
 
int main(){
	ios::sync_with_stdio(0);
	int sum,sz,t;
	lli k;
	cin >> t;
	while (t--){
		cin >> sum >> sz >> k;
		cout << print (sz, sum, k-1) << '\n';
	}
}
 
