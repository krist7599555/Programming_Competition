// spoj : ALLIZWEL
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
using namespace std;

const int  mxn = 110;
const char allizzwell[] = "ALLIZZWELL";
 
int r,c;
char in[mxn][mxn];
bool vi[mxn][mxn];
 
bool recur (int _i, int _j, const char* str){
	static const int x[] = {1,0,-1,0,1,1,-1,-1};
	static const int y[] = {0,-1,0,1,1,-1,1,-1};
	if (*str == '\0') return true;
	rep(k,0,8){
		int i = _i + x[k];
		int j = _j + y[k];
		if (-1 < i and i < r and -1 < j and j < c and
		    in[i][j] == *str and not vi[i][j]){
			
			vi[i][j] = true;
			if(recur(i,j,str+1)) 
				return true;
			vi[i][j] = false;
		}
	}
	return false;
}
 
int main(){
	cin.sync_with_stdio(0);
	int t;
  	cin >> t;
	while (t--){
		cin >> r >> c;
		rep(i,0,r)
			cin >> in[i];
		std::fill_n (*vi, mxn * mxn, false);
		rep(i,0,r){
		rep(j,0,c){
			if (in[i][j] == 'A'){
				vi[i][j] = true;
				if (recur (i,j,allizzwell+1)) goto out;
				vi[i][j] = false;
			}
		}}
		out:
		puts (count(*vi,*vi+mxn*mxn,true) ? "YES" : "NO");
	}
}
