// APIO 2007 debug
#include <bits/stdc++.h>
#include <iostream>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define all(x) (x).begin(),(x).end()
#define len(x) int((x).size())
using namespace std;
typedef std::vector<int> Vec;
typedef std::tuple<int,int,int> Data;

const int mxn = 1e5 + 10;
int cst[mxn];
int use[mxn];
int prv[mxn];
int nxt[mxn];

int main() {
	cin.sync_with_stdio(0);
	int n = input();
	int k = input();
	int lt = 0;
	std::priority_queue<Data, 
		std::vector<Data>, 
		std::greater<Data>> pq;
	rep(i,0,n){
		int x = input();
		prv[i] = i - 1;
		nxt[i] = i + 1;
		if (i){
			pq.emplace(cst[i] = x - lt, i - 1, i);
		}
		lt = x;
	}
	Vec ans;
	while (len(ans) != k){
		int c, b, e; // [cost, begin, end]
		tie(c, b, e) = pq.top(); pq.pop();
		if(!use[b] && !use[e]){
			use[b] = use[e] = true;
			assert (c == cst[e]);
			ans.push_back(c);
			int pv = prv[b]; // extend prv, nxt
			int nx = nxt[e];
			nxt[pv] = nx;
			prv[nx] = pv;
			// [a (m) b] >> [(a) m (b)] : inc cost = a - m + b
			cst[nx] += cst[b] - cst[e]; 
			if (pv != -1 and nx != n){ 
				pq.emplace(cst[nx], pv, nx);
	}}}
	printf("%lld", std::accumulate(all(ans), 0LL));
}
