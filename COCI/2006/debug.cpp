#include <bits/stdc++.h>
#include <iostream>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
using namespace std;

const int mxn = 310;

typedef uint64_t msk;
const msk lm = 64ULL;
const msk hb = 1ULL << (lm-1);

enum {h = 0, rh = 1, v = 2, rv = 3};
msk  dp[4][mxn][mxn]; // hor, ver
char in[mxn];

inline bool check(msk* it1, msk* it2, uint dis, int step){ // check it1 and it2 is mirror
	int rem = dis % lm;
	it1 += (rem-1) * step;
	it2 += (dis-1) * step;
	if (rem && (*it1 & ((1ULL << rem) - 1)) != (*it2 >> (lm - rem))) return false;
	it2 -= rem * step;
	for(; dis >= lm; dis -= lm){
		if (*(it1 += lm * step) != *it2) return false;
		it2 -= lm * step;
	}
	return true;
}

int main(){
	cin.sync_with_stdio(0);
	int r = input();
	int c = input();
	rep(i,0,r){
		cin >> in;
		rep(j,0,c){
			msk bit = in[j] - '0';
			dp[ v][i][j] = (i? dp[ v][i-1][j] << 1 : 0ULL) | (bit);
			dp[ h][i][j] = (j? dp[ h][i][j-1] << 1 : 0ULL) | (bit);
			dp[rv][i][j] = (i? dp[rv][i-1][j] >> 1 : 0ULL) | (bit? hb: 0ULL);
			dp[rh][i][j] = (j? dp[rh][i][j-1] >> 1 : 0ULL) | (bit? hb: 0ULL);
	}}
	int mx = 0;
	rep(_i,0,r){
	rep(_j,0,c){
		for(int sz: {2,3}){
			// O(n^2 / 64)
			for (int i = _i, j = _j;
				    0 <= i and i + sz <= r 
				and 0 <= j and j + sz <= c 
				and check(&dp[h][i][j], &dp[rh][i+sz-1][j], sz, 1)
				and check(&dp[v][i][j], &dp[rv][i][j+sz-1], sz, mxn);){
					mx = std::max(mx, sz);
					--i; --j; sz += 2; // extend square
	}}}}
	printf("%d", mx ?: -1);
	
}
