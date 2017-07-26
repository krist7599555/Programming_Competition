// spoj : FREQUENT
// by krist7599555
// RMQ

#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
using namespace std;
typedef long long lli;
typedef std::vector<int> Vec;
 
constexpr int mxn = 100000 + 10;
 
int n, q;
int ar[mxn];
int ia[mxn];
Vec sg(mxn + mxn);
 
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	while (n = input(), n != 0){
		q = input();
		sg.clear();
		int* p_ar = ar;
		int* p_ia = ia;
		int cnt = 1;
		int old = input();
		rep(i,1,n+1){
			int nw = i == n ? 1e8 : input();
			if (nw != old or i == n){
				std::iota(p_ia, p_ia + cnt, 0);
				std::fill(p_ar, p_ar + cnt, sz(sg));
				p_ar += cnt;
				p_ia += cnt;
				sg.push_back(cnt);
				cnt = 1;
				old = nw;
			}else{
				cnt++;
			}
		}
		ar[n] = sz(sg);
		assert (p_ar == ar + n);
		assert (p_ia == ia + n);
		int szsg = sz(sg);
		sg.insert(sg.end(), all(sg));
		loop(i,szsg)
			sg[i] = std::max(sg[i<<1], sg[i<<1|1]);
		loop(_,q){
			int l = input() - 1;
			int r = input();
			assert (l < r);
			if (ar[l] == ar[r-1]){
				printf("%d\n",ia[r-1] - ia[l] + 1);
			}else{
				int mx = std::max(sg[ar[l] + szsg] - ia[l], ia[r-1] + 1);
				for (l = ar[l] + szsg + 1, r = ar[r] + szsg; l != r; l >>=1, r >>= 1){
					if (l&1) mx = std::max(mx, sg[l++]);
					if (r&1) mx = std::max(mx, sg[--r]);
				}
				printf("%d\n",mx);
	}}}
}
