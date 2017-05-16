// spoj:GSS6
// by krist7599555
// hope you enjoy and gain a lot from this :)

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
using namespace std;
 
struct Node {
	
	int val, sz, prio;
	int mx, mxl, mxr, sm;
	Node *l, *r;
	
	Node (int v): val(v), sz(1), prio(rand()), mx(v), mxl(v), mxr(v), sm(v), l(0), r(0) {}
	
	inline void fixup (){
		sz = (l?l->sz:0) + (r?r->sz:0) + 1;
		sm = (l?l->sm:0) + (r?r->sm:0) + val;
		mxl = max( (l?l->mxl:-inf), (l?l->sm:0) + val + (r?max(0,r->mxl):0) );
		mxr = max( (r?r->mxr:-inf), (r?r->sm:0) + val + (l?max(0,l->mxr):0) );
		mx  = max({(l?l->mx :-inf), (r?r->mx:-inf), (l?max(0,l->mxr):0) + val + (r?max(0,r->mxl):0) });
	}
};
 
typedef Node* Nptr;
typedef const Nptr cNptr;
 
Nptr root = nullptr;
 
void split_at (cNptr nd, Nptr& l, Nptr& r, int pos){
	
	if (!nd) return void (l = r = nullptr);
	int szl = (nd->l ? nd->l->sz : 0) + 1;
	if (pos >= szl){
		l = nd;
		split_at (l->r, l->r, r, pos-szl);
		if(l) l->fixup();
	}else{
		r = nd;
		split_at (r->l, l, r->l, pos);
		if (r) r->fixup();
	}
}
 
void merge (Nptr& nd, cNptr l, cNptr r){
	
	if (!l or !r) return void (nd = l ?: r);
	if (l->prio > r->prio){
		merge (l->r, l->r, r);
		if (nd = l) nd->fixup();
	}else{
		merge (r->l, l, r->l);
		if (nd = r) nd->fixup();
	}
}
 
void insert_at (Nptr& nd, Nptr v, int pos){
	
	if (!nd) return void (nd = v);	
	if (v->prio > nd->prio){
		split_at (nd, v->l, v->r, pos);
		(nd = v)->fixup();
	}else{
		int szl = (nd->l ? nd->l->sz : 0) + 1;
		if (pos >= szl)
			insert_at (nd->r,v,pos-szl);
		else  	insert_at (nd->l,v,pos);
		
		if (nd) nd->fixup();
	}
}

void do_at (Nptr& nd, int pos, const function<void(Nptr&)>& op){
	
	int szl = (nd->l? nd->l->sz : 0) + 1;
	if (pos == szl) return op(nd);
	else{
		if (pos < szl)
			do_at (nd->l, pos, op);
		else  	do_at (nd->r, pos-szl, op);
		if (nd) nd->fixup();
	}
}
 
void replace_at (Nptr& nd, int v, int pos){
	return do_at (nd, pos, [v](Nptr& nd){ nd->val = v; nd->fixup(); });
}

void remove_at (Nptr& nd, int pos){
	return do_at (nd, pos, [ ](Nptr& nd){ merge (nd, nd->l, nd->r); });
}

int summary_query (int l,int r){
	
	Nptr nl = 0, nm = 0, nr = 0;
	split_at (root, root, nr, r);
	split_at (root, nl, nm, l-1); 
	
	int res = nm->mx;
	merge (root, nl, nm);
	merge (root, root, nr); 
	
	return res;
}
 
ostream& operator << (ostream& out, Nptr nd){
	return !nd ? out : out << nd->l << nd->val << ' ' << nd->r;
}
 
int main(){
	
	cin.sync_with_stdio(0);
	srand (time(0));
	
	char c;
	int n,v,q,x,y;
	
	cin >> n;
	rep(i,0,n)
		insert_at (root, new Node((cin>>v,v), i);
	cin >> q;
	while (q--){
		switch (cin >> c, c){
			case 'I' : 	cin >> x >> v;
					insert_at (root, new Node(v), x-1); break;
			case 'D' :	cin >> x;
					remove_at (root, x); break;
			case 'R' :	cin >> x >> v;
					replace_at (root, v, x); break;
			case 'Q' :	cin >> x >> y;
					printf("%d\n",summary_query(x,y)); break;
		};
	}
}
