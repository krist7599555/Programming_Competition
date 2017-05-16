// spoj : TRIP
// by krist7599555
// www.spoj.com/problems/TRIP/

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
#define ALL(x) (x).begin(),(x).end()
using namespace std;

const int mxn = 100;

int  n1,n2;
char in1[mxn];
char in2[mxn];
int  dp [mxn][mxn];
std::set <string> ans;
std::map <string,bool> isCal[mxn][mxn];

void back_track (int i, int j, string word){ // solution 1
	if (isCal[i][j].count(word)) return;
	if (i == 0 or j == 0) return void (ans.insert(word));
	isCal[i][j][word] = true;
	if (    in1[i] ==   in2[j]) back_track (i-1, j-1, in1[i] + word);
	if (dp[i-1][j] == dp[i][j]) back_track (i-1, j  , word);
	if (dp[i][j-1] == dp[i][j]) back_track (i  , j-1, word);
}

void print_lexico (int ii, int jj, int sz){ // solution 2
	static char o[mxn]{};
	if (sz == dp[n1][n2]) return o[sz]='\0', puts(o), void(0);
	rep(ch,'a','z'+1){
	rep(i,ii,n1+1){ if (in1[i] == ch){
	rep(j,jj,n2+1){ if (in2[j] == ch){
		if (dp[i][j] == sz + 1){
			o[sz] = ch;
			print_lexico (i+1,j+1,sz+1);
			goto out;
		}
	}}}} out:;
	}
}

#define LEXICO
#define BACK_TRACK

void solve(){
	ans.clear();
	std::fill_n (dp[0], mxn * mxn, 0);
	rep(i,1,n1+1){
	rep(j,1,n2+1){
		isCal[i][j].clear();
		dp[i][j] = in1[i] == in2[j] ? 
			dp[i-1][j-1] + 1 : 
			max(dp[i-1][j], dp[i][j-1]);
	}}
	#ifdef BACK_TRACK	
		back_track (n1,n2,"");	// solution 1	
		copy(ALL(ans),ostream_iterator<string>(cout," "));
	#elif LEXICO 		
		print_lexico (0,0,0);	// solution 2
	#endif
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
      cin >> (in1+1) >> (in2+1);
      n1 = strlen(in1+1);
      n2 = strlen(in2+1);
      solve();
    }
}

