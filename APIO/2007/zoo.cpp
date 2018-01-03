// APIO 2007 : zoo 
// by krist7599555
#include <bits/stdc++.h>
#include <iostream>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
using namespace std;
typedef std::vector<int> Vec;

const int inf = 1e7;
const int mxn = 1e4;

int add[mxn][32];

int main(){
	cin.sync_with_stdio(0);
	int n = input();
	loop(_,input()){
		int x = input() + 4;
		int f = input();
		int l = input();
		int rd[2] = {f, l};
		int ar[2]{}; // fear, like
		rep(i,0,2){
			loop(_,rd[i]){
				int dif = x - input();
				int tmp = dif >= 5 ? dif - n : dif < 0 ? dif + n : dif;
				assert (0 <= tmp and tmp < 5);
				ar[i] |= 1 << tmp;
		}}
		loop(m, 32){ // lost any fear || have any like : -max sat-
			if((~m & ar[0]) or (m & ar[1])){
				add[x % n][m] += 1;
		}}
	}
	int mx = 0;
	loop(init, 32){ // try all cycle start with different initial bitmask
		Vec dp(32, -inf); dp[init] = 0;
		rep(i,0,n){
			Vec tm(32);
			loop(m,32)
				tm[m] = add[i][m] + std::max(dp[m>>1], dp[m>>1|0x10]);
			dp = std::move(tm);
		}
		mx = std::max(mx, dp[init]);
	}
	printf("%d\n", mx);
}
