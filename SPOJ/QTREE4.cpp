// spoj : QTREE4
// by krist7599555
// so proud with this task :)

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i<(n);++i)
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) int((x).size())
#define fi first
#define se second
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
typedef long long lli;
typedef std::vector<int> Vec;
typedef std::pair<int,int> pii;
 
typedef __gnu_pbds::priority_queue<int> PQ_type;
const int MAXN = 1e5;
const int inf  = 1e9;
constexpr int _log2 (int v){ return 31 - __builtin_clz(v); } 
 
 
namespace Graph {
	
	struct Edge { int v,w; 
		bool operator < (const Edge& a) const { 
			return tie(v,w) < tie(a.v,a.w); 
	}};
	
	int n;
	set<Edge> conec[MAXN];
	
	namespace Distance {
		
		const int mxlg = 1 + _log2(2 * MAXN);
		int cnt = 0;
		int val [MAXN]{};
		int pos [MAXN];
		int dept[MAXN];
		int sp  [MAXN * 2][mxlg];
		
		void dfs (int now, int pa){
			pos [now] = cnt;
			dept[now] = pa == -1 ? 0 : (dept[pa] + 1);
			sp  [cnt++][0] = now;
			for (const Edge& nex : conec[now]){
				if (nex.v != pa){
					val[nex.v] = val[now] + nex.w;
					dfs(nex.v,now);
					sp[cnt++][0] = now;
				}
			}
		}
		
		void init_sp (){
			dfs(0,-1);
			assert (cnt == n + n - 1);
			rep (lg, 1, mxlg)
			rep (i, 0, cnt - (1<<lg)){
				sp[i][lg] = dept[sp[i][lg-1]] < dept[sp[i+(1<<(lg-1))][lg-1]] ? 
								 sp[i][lg-1]  : 	 sp[i+(1<<(lg-1))][lg-1];
			}
		}
		
		inline int lca (int a,int b){
			tie(a,b) = minmax(pos[a],pos[b]);
			int lg = 31 - __builtin_clz (++b - a);
			return dept[sp[a][lg]] < dept[sp[b-(1<<lg)][lg]] ? sp[a][lg] : sp[b-(1<<lg)][lg];
		}
		
		inline int dist (int a,int b){
			return val[a] + val[b] - 2 * val[lca(a,b)];
		}
	}
	
	namespace Decompost {
				
		struct At { 
			int nd,group,pos; 
		};
		
		struct MaxSeg {
			
			int  n;
			int* v;
			
			inline void init(int _n){
				n = _n;
				v = new int[n << 1];
			}
			
			void build(){
				for (int i = n; --i;)
					v[i] = max(v[i<<1], v[i<<1|1]);
			}
			//~ inline void update_one(int x, int _v){
				//~ v[x+=n] = _v;
			//~ }
			inline void update_lg (int x, int _v){
				v[x+=n] = _v;
				for (; x != 1; x >>= 1)
					v[x>>1] = max(v[x],v[x^1]);
			}
			//~ inline int get_max(){
				//~ return v[1];
			//~ }
		};
		
		struct PiiGroupSeg {
			
			static PQ_type PQ;
			PQ_type::point_iterator poi;
			
			int n;
			vector<pii>    s;
			vector<MaxSeg> v;
			
			inline void init (int _n){
				n = _n;
				s.resize (n * 2);
				v.resize (n);
			}
			
			inline void merge (pii& res, const pii& a, const pii& b){
				res = minmax(a.se,b.se);
				res.fi = max (max(a.fi,b.fi), res.fi);
			}
			
			inline void update_one (int g, int _x, int _v){
				//~ v[g].update_one(_x,_v);
				v[g].v[v[g].n+_x] = _v;
			}
			
			void update_lg (int g, int _x, int _v){
				v[g].update_lg(_x,_v);
				//~ s[g+n] = {-inf, v[g].get_max() };
				s[g+n] = {-inf, v[g].v[1] };
				for (g += n; g != 1; g >>= 1){
					merge (s[g>>1], s[g], s[g^1]);
				}
				return PQ.modify (poi, s[1].fi + s[1].se);
			}
			
			void build(){
				rep(i,0,n)
					v[i].build(),
					s[i+n] = { -inf, v[i].v[1] };
					//~ s[i+n] = { -inf, v[i].get_max() };
				for (int i = n; --i;)
					merge (s[i], s[i<<1], s[i<<1|1]);
				poi = PQ.push (s[1].fi + s[1].se);
			}
			
		};
		
		int  sz[MAXN];
		int  still;
		bool color[MAXN];
		
		vector<At> lookup[MAXN]; // [nd,pos]
		PiiGroupSeg seg[MAXN];   // [mn,mx]
		
		int root_nd;
		Vec tree[MAXN];
		
		int dfs (int now, int pa){
			sz[now] = 1;
			for (const Edge& nex : conec[now])
				if (nex.v != pa)
					sz[now] += dfs(nex.v,now);
			return sz[now];
		}
		
		int decompost (int root){ // return root			
			int allsz = dfs (root,-1);
			up:
			for (const Edge& nex : conec[root]){
				if (sz[nex.v] >= allsz >> 1 and sz[nex.v] < sz[root]){
					root = nex.v;
					goto up;
				}
			}
			for (const Edge& nex : conec[root]){
				conec[nex.v].erase (Edge {root, nex.w});
				tree [root ].push_back (decompost(nex.v));
			}
			sz[root] = allsz;
			return root;
		}
 
			
		void dfs_init (int now){
			
			static vector<At> stk;
			
			for (At& at : stk){ // write to top
				seg[at.nd].update_one (at.group, at.pos, Distance::dist(now,at.nd));
				lookup[now].push_back (at);
				at.pos++;
			}
			
			stk.push_back (At{ now, 0, 0});
			for (int nex : tree[now]){
				dfs_init (nex);
				stk.back().group++;
				stk.back().pos = 0;
			}
			
			lookup[now].push_back(At{ now, stk.back().group, 0}); // cyc
			seg[now].update_one (stk.back().group++, 0, 0);
			
			assert (stk.back().group == seg[now].n);
			seg[now].build();
			
			stk.pop_back();
		}
	
		
		void init_seg(){	
			root_nd = decompost(0);
			fill_n (color, still = n, true);
			rep(i,0,n){ // allocate
				seg[i].init (tree[i].size() + 1);
				rep(j,0u,tree[i].size())
					seg[i].v[j].init (sz[tree[i][j]]);
				seg[i].v[tree[i].size()].init(1);
			}
			dfs_init (root_nd);
		}
		
		void ans (){
			if (still == 0) puts("They have disappeared."); else
			if (still == 1) puts("0"); else
			if (still >  1) printf("%d\n",max(0,PiiGroupSeg::PQ.top())); 
		}
		
		void toggle (int col){
			(color[col] ^= true) ?  ++still : --still;
			for (At& up : lookup[col])
				seg[up.nd].update_lg (up.group, up.pos, color[col] ? Distance::dist(col,up.nd) : -inf);
		}
	};
	
};
 
PQ_type Graph::Decompost::PiiGroupSeg::PQ;
 
int main(){
	
  cin.sync_with_stdio(0);
  cin.tie(0);
	using namespace Graph;
	
	cin >> n;
	rep(i,1,n){
		int u,v,w;
		cin >> u >> v >> w;
		conec[u-1].insert(Edge{v-1,w});
		conec[v-1].insert(Edge{u-1,w});
	}
 
	Graph::Distance ::init_sp();
	Graph::Decompost::init_seg();
	
	char cm;
	int q,nd;
	cin >> q;
	while (q--){		
		cin >> cm;
		if (cm == 'A') Decompost::ans(); else
		if (cm == 'C') Decompost::toggle((cin>>nd,nd-1));
		else throw "fuck";
	}
	
}
