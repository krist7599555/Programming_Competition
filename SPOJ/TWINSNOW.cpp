// spoj : TWINSNOW
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
#define ALL(x) (x).begin(),(x).end()
using namespace std;
typedef std::vector<int> Vec;

int main(){

	cin.sync_with_stdio(0);
	int n;
	cin >> n;
	vector<Vec> vec;
	rep(i,0,n){
		Vec tmp(6),mn;
		rep(i,0,6) cin >> tmp[i];
		mn = tmp;
		rep(_,0,2){
			if(_) reverse(ALL(tmp));
			rep(i,0,6){
				rotate (tmp.begin(), tmp.begin()+1, tmp.end());
				mn = min(mn,tmp);
		}}
		vec.emplace_back(move(mn));
	}
	sort(ALL(vec));
	bool alike = false;
	rep(i,1,n) if (not alike and vec[i] == vec[i-1]) alike = true;
	puts (alike ? "Twin snowflakes found." : "No two snowflakes are alike.");

}
