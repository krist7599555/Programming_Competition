#include <bits/extc++.h>
#include <iostream>
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

struct Node{
	int sz;
	lli sm;
	Node *l,*r;
	
	Node(): sz(0), sm(0), l(0), r(0) {}
	Node(lli v): sz(1), sm(v), l(0), r(0) {}
	Node(Node* _l, Node* _r): sz(_l->sz + _r->sz), sm(_l->sm + _r->sm), l(_l), r(_r) {}
	
	Node* add (int pl, int pr, int px, int v){
		int pm = (pl + pr) >> 1;
		if (pl + 1 == pr) return new Node(v);
		if (px < pm) return new Node(l->add(pl,pm,px,v),r);
		else 		 return new Node(l,r->add(pm,pr,px,v));
	}
	
	static int solve (int pl, int pr, Node* l, Node* r, int money){
		if (pl + 1 == pr) return money >= r->sm - l->sm ? r->sz - l->sz : 0;
		int pm = (pl + pr) >> 1;
		int sz = r->l->sz - l->l->sz;
		lli sm = r->l->sm - l->l->sm;
		if (money < sm) return solve (pl,pm,l->l,r->l,money);
		else return sz + solve (pm,pr,l->r,r->r,money-sm);
	}
};

struct Inp{
	int cost;
	int leader;
	int cost_pos;
	int sz;
	Vec conec;
};

const int mxn = 100100;

int N,Money;

Vec seq;
Inp inp[mxn];
Node* per[mxn];

int travel (int nw){
	seq.push_back(nw);
	inp[nw].sz = 0;
	for (int i = 0; i != SZ(inp[nw].conec); ++i){
		int nx = inp[nw].conec[i];
		inp[nw].sz += travel(nx);
	}
	return inp[nw].sz + 1;
}

struct cmp_cost {
	bool operator()(int a,int b){ 
		return inp[a].cost < inp[b].cost; 
	}
};

int main(){
	
	//~ freopen("debug.txt","r",stdin);
    cin.sync_with_stdio(0);
	cin >> N >> Money;
	
	for (int pa, i = 1; i <= N; ++i){ // input
		cin >> pa >> inp[i].cost >> inp[i].leader;
		inp[pa].conec.push_back(i);
	
	}
	{	// cmpss cost
		Vec cmpss;
		cmpss.resize(N);
		iota(ALL(cmpss),1);
		sort(ALL(cmpss),cmp_cost());
		for (int i = 0; i != N; ++i) inp[cmpss[i]].cost_pos = i;
	}
	
	travel(0); // tree seq
	assert (SZ(seq) == N + 1);
	
	per[0] = new Node(); per[0]->l = per[0]->r = per[0];
	for (int i = 1; i <= N; ++i){ // persistant
		int root = seq[i];
		per[i] = per[i-1]->add (0, N, inp[root].cost_pos, inp[root].cost);
	}
	
	lli ans = 0;
	for (int i = 1; i <= N; ++i){ // query
		int root = seq[i];
		ans = max (ans, 
			lli(inp[root].leader) * Node::solve(0, N, per[i-1], per[i+inp[root].sz], Money));
	}
	cout << ans;
}

