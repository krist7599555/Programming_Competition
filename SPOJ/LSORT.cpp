// spoj : LSORT
// by krist7599555

#include <bits/stdc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i<=int(n);++i)
#define loop(i,n) for(int i = (n); i--;)
#define input() (*std::istream_iterator<int>(cin))
using namespace std;

const int mxn = 1010;

int n;
int pos[mxn];
int kth[mxn][mxn]{}; // kth[v][pos] = number of v = [1..val] in p = [1..pos]
int dp [mxn][mxn]{}; // dp[l][r] = cost to sort [l..r] = std::min ([l+1..r] + xl, [l..r-1] + xr)

inline int cost(int vl, int vr, int pos){ // sum [1..vl) | (vr..n] in p = [1..pos]
	return kth[n+1][pos] - kth[vr][pos] + kth[vl-1][pos];
}

int main(){
	ios::sync_with_stdio(0);
	loop(_,input()){
		std::fill_n (kth[0], mxn * mxn, 0);
		n = input();
		rep(i,1,n){
			int v = input();
			pos[v] = i;
			kth[v][i] = 1;
		}
		rep(i,1,n+1){
		rep(j,1,n+1){
			kth[i][j] += kth[i-1][j] + kth[i][j-1] - kth[i-1][j-1];
		}}
		rep(sz,1,n){
			for (int l = 1, r = sz; r <= n; ++l, ++r){
				int v1 = dp[l+1][r] + ::cost(l+1, r, pos[l]) * sz;
				int v2 = dp[l][r-1] + ::cost(l, r-1, pos[r]) * sz;
				dp[l][r] = std::min(v1, v2);
			}
		}
		cout << dp[1][n] << '\n';
	}
	
}
