// spoj : AMR11H
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
#define SZ(x) int((x).size())
#define fi first
#define se second
using namespace std;
typedef long long lli;

const int mod = 1e9 + 7;
const int mxn = 1e5;

int n,t;
int in [mxn];
lli pw2[mxn];

int main(){

	cin.sync_with_stdio(0);
	cin.tie(0);
	pw2[0] = 1;
	rep(i,1,mxn){
		pw2[i] =  pw2[i-1] * 2 % mod;
	}
	cin >> t;
	while (t--){
		cin >> n;
		rep(i,0,n) cin >> in[i];
		auto mnmx = minmax_element(in,in+n);
		if (*mnmx.fi == *mnmx.se){ // min == max
			printf ("%lld %lld\n",(lli(n)*(n-1)/2 + n) % mod, pw2[n]-1);
			continue;
		}
		queue<int> mn,mx;
		rep(i,0,n){
			if (in[i] == *mnmx.fi) mn.push(i); else
			if (in[i] == *mnmx.se) mx.push(i);
		}
		lli subseq = (pw2[SZ(mn)]-1) * (pw2[SZ(mx)]-1) % mod * pw2[n-SZ(mx)-SZ(mn)] % mod;
		lli substr = 0;
		rep(i,0,n){
			
			if (not mn.empty() and mn.front() < i) mn.pop();
			if (not mx.empty() and mx.front() < i) mx.pop();
			
			if (not mn.empty() and not mx.empty()) 
				substr += n - max (mn.front(),mx.front());
		}
		printf("%lld %lld\n",substr % mod, subseq);
	}
}

