// spoj : MINVEST
// by krist7599555

#include <bits/stdc++.h>
using namespace std;

const int mxn = 5e4; // pow(1.1,40) * 1e6 / 1e3
int dp[mxn];

int main(){
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--){
		int day,n,money;
		cin >> money >> day >> n;
		std::fill_n (dp, mxn, 0);
		while (n--){
			int bond, profit;
			cin >> bond >> profit;
			assert (bond % 1000 == 0);
			bond /= 1000;
			for (int i = bond; i < mxn; ++i){ // bond can be very large and can not buy, so used i < mxn
				dp[i] = max(dp[i], dp[i-bond] + profit);
			}
		}
		std::partial_sum (dp, dp + mxn, dp, ptr_fun<cint&,cint&,cint&>(std::max<int>));
		while (day--){
			money += dp[money/1000];
		}
		cout << money << '\n';
	}
}
