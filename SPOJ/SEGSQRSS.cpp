#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
using namespace std;
typedef long long lli;

struct Node {

private:

	const int l,m,r,sz;
	lli  sm, sq;
	bool lz;
	int  set, add;
	Node *nl, *nr;
	
	inline void __set (int v){  
		lz  = true;
		set = v;
		add = 0;
		sm  = sz * v;
		sq  = sz * v * v;
	};

	inline void __add (int v){
		add += v;
		sq  += (2 * add * sm) + (sz * add * add);
		sm  += (add * sz);
		// sum {(ai + m) ** 2} 
		// = sum { ai**2 + 2*ai*m + m**2 } 
		// = sum { ai**2 } + 2m*sum{ai} + sum{m**2}
	};
	
	inline void __fixup(){
		sm = nl->sm + nr->sm;
		sq = nl->sq + nr->sq;
	}
	
	inline void __fixdown(){
		for (Node* nx : {nl,nr}){
			if (lz)  nx->__set (set);
			if (add) nx->__add (add);
		}
		lz  = false;
		add = 0;
	}
	
	void _travel (int bl, int br, const function<void(Node*)>& op){
		if (bl <= l and r <= br){
			op(this);
		}else{
			__fixdown();
			if (bl < m) nl->_travel (bl, br, op);
			if (m < br) nr->_travel (bl, br, op);
			__fixup();
		}
	}
	
public:

	Node (int _l, int _r, int ar[]): 
			l(_l), m((_l+_r)>>1), r(_r), sz(r-l), lz(false), set(0), add(0) {
		if (l + 1 == r){
			nl = nr = nullptr;
			this->__set(ar[l]);
		}else{
			nl = new Node(l,m,ar);
			nr = new Node(m,r,ar);
			__fixup();
		}
	}
	
	~Node(){
		if (nl) delete nl;
		if (nr) delete nr;
	}
	
	void add_val (int bl, int br, int v){
		return _travel (bl, br, bind2nd (mem_fun (&Node::__add), v));
	}
	
	void set_val (int bl, int br, int v){
		return _travel (bl, br, bind2nd (mem_fun (&Node::__set), v));
	}
	
	lli sum_val (int bl, int br){
		lli res = 0; 
		_travel (bl, br, [&res](Node* nd){ res += nd->sq; });
		return res;
	}
	
};


const int mxn = 1e5;

int main(){
	
  cin.sync_with_stdio(0);
	int tt, n, q;
	int in [mxn];
	cin >> tt;
	rep(t,0,tt){
		printf("Case %d:\n",t+1);
		cin >> n >> q;
		rep(i,0,n) cin >> in[i];
		Node root(0,n,in);
		int cm,l,r,v;
		while (q--){
			switch(cin >> cm >> l >> r, cm){
				case 0 : root.set_val (l-1, r, (cin >> v, v)); break; //set
				case 1 : root.add_val (l-1, r, (cin >> v, v)); break; //add
				case 2 : printf("%lld\n",root.sum_val(l-1,r)); break; //query
		}}		
	}
}

