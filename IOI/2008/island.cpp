#include <bits/stdc++.h>
#include <iostream>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(auto i=(k);i!=(n);++i)
#define all(x) (x).begin(),(x).end()
#define len(x) (x).size()
#define fi first
#define se second
using namespace std;
typedef long long lli;
typedef std::pair<lli,lli> pii;
typedef std::vector<lli> Vec;

const int mxn = 1e6 + 10;

lli solve_cycle(Vec nod, Vec pth){
#ifdef _brute_force_
	lli ans = 0;
	pth.insert(pth.begin(), 0);
	std::partial_sum(all(pth), pth.begin());
	lli cyc = pth.back();
	rep(i,0,len(nod)){
	rep(j,0,i){
		lli dis = pth[i] - pth[j];
		ans = std::max(ans, nod[i] + nod[j] + std::max(dis, cyc - dis));
	}}
	return ans;
#else
	lli ans = 0;
	int sz = len(nod);
	pth.reserve(2 * len(pth) + 1);
	std::copy(all(pth), std::back_inserter(pth));
	std::partial_sum(all(pth), pth.begin());
	pth.insert(pth.begin(), 0);
	std::deque<pii> dq;
	rep(i,0,sz<<1){
		if (!dq.empty() and dq.front().se + sz == i) dq.pop_front();
		if (!dq.empty()){
			ans = std::max(ans, nod[i%sz] + pth[i] - dq.front().fi);
		}
		lli nw = pth[i] - nod[i%sz];
		while (!dq.empty() and nw < dq.back().fi) dq.pop_back();
		dq.emplace_back(nw, i);
	}
	return ans;
#endif
}

lli maxx[mxn];
lli cost[mxn];
int dege[mxn];
pii edge[mxn];

int main(){
	cin.sync_with_stdio(0);
	const int n = input();
	for(int u = 1; u <= n; ++u){
		int v = input();
		edge[u] = pii(v, input());
		dege[v]++;
	}
	std::queue<int> que; // DAG
	for (int i = 1; i <= n; ++i){
		if (!dege[i]){
			que.push(i);
	}}
	while (not que.empty()){
		int u = que.front(); que.pop();
		pii v = edge[u];{
			auto nw_cost = cost[u] + v.se;
			maxx[v.fi] = std::max({maxx[v.fi], nw_cost + cost[v.fi], maxx[u]});
			cost[v.fi] = std::max({cost[v.fi], nw_cost});
			if (!--dege[v.fi]){
				que.push(v.fi);
	}}}
	std::vector<bool> chk(n + 1, false);
	lli ans = 0;
	for (int i = 1; i <= n; ++i){
		assert(dege[i] <= 1);
		if (!chk[i] and dege[i]){
			lli tree = 0;
			Vec nod, pth;
			int j = i;
			do{ // cycle finding
				chk[j] = true;
				assert(dege[j] == 1);
				tree = std::max(tree, maxx[j]);
				nod.push_back(cost[j]);
				pth.push_back(edge[j].se);
				j = edge[j].fi;
			}while(j != i);
			ans += std::max(tree, solve_cycle(std::move(nod), std::move(pth)));
		}
	}
	printf("%lld\n", ans);
}
