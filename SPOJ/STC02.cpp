// spoj : STC02
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i<(n);++i)
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
typedef long long lli;

const int mxn = 5e5 + 10;
const int mxk = 2;

int n;
lli _mod  [mxk]{lli(1e9+7),lli(1e9+21)};
lli _sp[2][mxk][mxn];
lli _pw2  [mxk][mxn];
char str  [mxn];

#define to_val(g,at,sz,k) \
	((_sp[g][k][at] - (_pw2[k][sz] * _sp[g][k][at+sz]) % _mod[k] + _mod[k]) % _mod[k])

int comp (int p1, int p2){
	int l = 0, r = min (n-p1, n-p2) + 1;
	while (l != r){
		int m = (l + r) >> 1;
		if (to_val(0,p1,m,0) == to_val(1,p2,m,0) and
			to_val(0,p1,m,1) == to_val(1,p2,m,1)) 
				l = m + 1;
		else 	r = m;
	}
	return l-1;
}

int main(){
	
    	cin.sync_with_stdio(0);
    
   	auto pre_process = []{
		rep(i,0,mxn){
		rep(k,0,mxk){
			_pw2[k][i] = i ? _pw2[k][i-1] * 2 % _mod[k] : 1;
	}}};
	
	auto build = [](lli s[][mxn]){
		for (int i = n; i--;){
		for (int k = 0; k != mxk; ++k){
			s[k][i] = (s[k][i+1] * 2LL + str[i] - '0') % _mod[k];
	}}};
	
	pre_process();
	cin >> n >> str;
	
	rep(_,0,2){
		if (_) 	reverse(str,str+n),
				transform(str,str+n,str,bind2nd(bit_xor<char>(),'1'^'0'));
		build (_sp[_]);
	}
	
	lli res = 0;
	rep(i,0,n) res += comp(i,n-i);
	cout << res;
}

