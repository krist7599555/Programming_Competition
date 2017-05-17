// spoj : GNYR09F 
// by krist7599555
// www.spoj.com/problems/GNYR09F/

#include <bits/extc++.h>
#include <iostream>
using namespace std;

const int mxn = 1010;
int  dp [mxn][mxn][2];
bool cal[mxn][mxn][2]; 
// [x][1],g  = ([x-1][1],g-1 + [1]) + ([x-1][0].g + [1])
// [x][0],g  = ([x-1][1],g   + [0]) + ([x-1][0].g + [0])

int way (int l, int g, bool b){ // [strLen][Group][Bit1/0]
	if (g == -1) return 0;
	if (l ==  1) return g == 0;
	if (cal[l][g][b]) return dp[l][g][b];
	return 
		cal[l][g][b] = true,
		dp [l][g][b] = way(l-1,g-b,true) + way(l-1,g,false);
}

int main(){
  	cin.sync_with_stdio(0); 
	int t; 
  	cin >> t;
	while (t--){
		int no,l,g; 
		cin >> no >> l >> g;
		printf("%d %d\n",no,way(l+1,g,false));
	}
}
