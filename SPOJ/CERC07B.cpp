// spoj : CERC07B
// by krist759955
// light out puzzle

#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
using namespace std;

const int mxn = 17;

int  R, C;
char in[mxn][mxn];
char cp[mxn * mxn];

void flip(int i, int j){
	static const int dx[] = {0,1,0,-1,0};
	static const int dy[] = {0,0,-1,0,1};
	loop(k,5){
		int _i = i + dx[k];
		int _j = j + dy[k];
		if (-1 < _i and _i < R and
			-1 < _j and _j < C){
			in[_i][_j] ^= 'X'^'.';	
	}}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	while (cin >> R >> C, R or C){
		loop(i,R)
			cin >> in[i];
		std::copy(*in, *in + mxn * mxn, cp);
		int mn = 1e8;
		loop(up, 1 << C){
			int cnt = 0;
			loop(j, C){
				if (up & 1 << j){
					cnt++;
					flip(0, j);
			}}
			rep(i,0,R-1){
			rep(j,0,C){
				if (in[i][j] == 'X'){
					++cnt;
					flip(i+1, j);
				}		
			}}
			if (not std::count(in[R-1], in[R-1] + C, 'X')){
				mn = std::min(mn ,cnt);
			}
			std::copy(cp, cp + mxn * mxn, *in);
		}
		printf(mn > R * C ? "Damaged billboard.\n": "You have to tap %d tiles.\n", mn);
	}
}
