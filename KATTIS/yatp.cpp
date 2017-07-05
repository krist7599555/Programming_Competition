// https://open.kattis.com/problems/yatp
// centroid decomposition + convec hull trick
#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i<=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
using namespace std;
typedef long long lli;
typedef std::pair<lli,lli> pii;
typedef std::vector<int> Vec;

const int mxn = 2e5 + 10;

class ConvecHull : public __gnu_pbds::tree<pii,__gnu_pbds::null_type,std::greater<pii>> {
	
	protected:

		typedef __gnu_pbds::tree<pii,null_type,std::greater<pii>> tree_type;
		typedef ConvecHull this_type;
		
		inline bool bad (iterator it){
			if (it == begin() or next(it) == end()) return false;
			auto prv = prev(it);
			auto nex = next(it);
			return nex->fi == it->fi or cross(*prv,*nex) <= cross(*prv,*it);
		}
		
	public:
	
		static const lli inf = 1e16;
		
		static inline lli get (const pii& p, int x){
			return p.fi * x + p.se;
		}
		static inline double cross (const pii& p1, const pii& p2){
			// mx + c == nx + d, x == (d - c) / m - n
			return double(p2.se - p1.se) / (p1.fi - p2.fi);
		}

		inline bool insert (pii p){
			iterator it; bool b;
			tie(it,b) = tree_type::insert(p);
			if (not b)   return false; // duplicate
			if (bad(it)) return erase(it), false; // bad one
			while (it != begin()     and bad(prev(it)))	erase(prev(it)); // bad left
			while (next(it) != end() and bad(next(it)))	erase(next(it)); // bad right
			return true;
		}
		inline iterator get_best (int x){
			auto nd = node_begin();
			auto en = node_end();
			iterator res = end();
			while (nd != en){
				if (res == end() or get(**nd, x) < get(*res, x)) res = *nd;
				double left_x = *nd == begin() ? -inf : ConvecHull::cross(*prev(*nd), **nd);
				nd = double(x) < left_x ? nd.get_l_child() : nd.get_r_child();
			}
			return res;
		}
		
		ConvecHull (){}
};

namespace Graph {
	
	int n;
	int pa  [mxn];
	int sz  [mxn];
	lli ans [mxn];
	lli dist[mxn];
	lli pnal[mxn]; // penalty
	bool comp[mxn];
	std::vector<pii> edge[mxn]; // connect edge (v, w)
	
	Vec splash_size (int nd, int init_cost = 0){
		assert (not comp[nd]);
		std::vector<int> stk;
		std::queue <int> bfs; 
		bfs.emplace(nd); 
		pa[nd] = 0;
		dist[nd] = init_cost;
		while (not bfs.empty()){
			int u = bfs.front(); bfs.pop();
			sz[u] = 1;
			stk.push_back(u);
			
			for (const pii& nx : edge[u]){
				int v = nx.fi;
				if (not comp[v] and v != pa[u]){
					bfs.push(v);
					pa[v] = u;
					dist[v] = dist[u] + nx.se;
		}}}
		for (auto it = stk.rbegin(); it != stk.rend(); ++it){
			sz[pa[*it]] += sz[*it];
		}
		assert (not stk.empty());
		return stk;
	}
	
	void decompose (int root = 1){
		int alsz = splash_size(root).size();
		if (alsz == 1) return;
		top:
		for (const pii& nx : edge[root]){
			if (not comp[nx.fi] 
				and sz[nx.fi] < sz[root]
				and sz[nx.fi] >= alsz / 2){
					root = nx.fi;
					goto top;
		}}
		
		Vec v = splash_size (root);
		ConvecHull ch;
		for (int i : v) ch.insert(pii(pnal[i], dist[i]));
		
		for (int i : v){
			pii pi = *ch.get_best(pnal[i]);
			lli sm = ConvecHull::get(pi, pnal[i]) + dist[i];
			ans[i] = std::min(ans[i], sm);
			if (ans[i] < 0) exit(1);
		}
		comp[root] = true;
		for (const pii& nx : edge[root])
			if (not comp[nx.fi])
				decompose(nx.fi);
	}
};

int main(){
	using namespace Graph;
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	rep(i,1,n){
		cin >> pnal[i];
		ans[i] = pnal[i] * pnal[i];
		assert (ans[i] >= 0);
	}
	loop (_,n-1){
		int u, v, w;
		cin >> u >> v >> w;
		edge[u].emplace_back(v, w);
		edge[v].emplace_back(u, w);
	}
	decompose();
	cout << accumulate (ans+1, ans+1+n, 0LL);
}
