// spoj : PIHU1
// krist7599555
// binary search

#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
using namespace std;
typedef long long lli;
 
int in[1000];
 
int main(){
	cin.sync_with_stdio(0);
	loop(_,input()){
		int n = input();
		loop(i,n)
			cin >> in[i];
		std::sort(in, in + n);
		lli  des;
		cin >> des;
		bool ok = false;
		rep(i,0,n){
		rep(j,0,i){
			lli vl = des - in[i] - in[j];
			int*it = std::lower_bound(in, in + j, vl);
			if (it != in + j and *it == vl){
				ok = true;
				break;
		}}}
		puts(ok ? "YES" : "NO");
	}
}
