// https://open.kattis.com/problems/crane2
#include <bits/stdc++.h>
#include <iostream>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) x.begin(), x.end()
#define fi first
#define se second
using namespace std;
typedef std::string Str;
typedef std::vector<int> Vec;
typedef std::pair<int,int> pii;

const int inf = 1e9;

struct  Node;
typedef Node* Ptr;
struct Node {
    int sz, vl, prio;
    Ptr p, l, r;
    Node(int v): sz(1), vl(v), prio(std::rand()), p(0), l(0), r(0) {}
};

inline void fixup (Ptr& p){
    if(p){
        p->sz = (p->l ? p->l->sz : 0) + 1 + (p->r ? p->r->sz : 0);
        if (p->l) p->l->p = p;
        if (p->r) p->r->p = p;
    }
}

void split (Ptr& nd, Ptr& a, Ptr& b, int kth){
    if (!nd)
        return void(a = b = nullptr);    
    int sz_l = nd->l ? nd->l->sz : 0;
    if (sz_l < kth)
        a = nd, 
        split (nd->r, a->r, b, kth - sz_l - 1),
        fixup (a);
    else
        b = nd, 
        split (nd->l, a, b->l, kth), 
        fixup (b);
}

void merge (Ptr& nd, Ptr& a, Ptr& b){
    if (!a or !b) return void(nd = a ?: b);    
    if (a->prio > b->prio)
        merge (a->r, a->r, b),
        fixup (nd = a);
    else
        merge (b->l, a, b->l),
        fixup (nd = b);
}


std::ostream& operator << (std::ostream& o, Ptr p){
    return p ? o << p->l << p->vl << ' ' << p->r : o;
}

Ptr insert_at (Ptr& base, Ptr& obj, int kth){
    Ptr tmp = nullptr;
    ::split (base, base, tmp, kth);
    ::merge (base, base, obj);
    ::merge (base, base, tmp);
    return obj;
}

void rotate (Ptr& base, int l, int m, int r){
    Ptr pl(0), pm(0), pr(0);
    ::split(base, base, pr, r);
    ::split(base, base, pm, m);
    ::split(base, base, pl, l);
    std::swap(pl, pm);
    ::merge(base, base, pl);
    ::merge(base, base, pm);
    ::merge(base, base, pr);
}

inline int pos_of (Ptr p){
    int sm = p->l ? p->l->sz : 0;
    while (p){
        int nw = p->vl;
        p = p->p;
        if (p and p->r and p->r->vl == nw){
            sm += p->l ? p->l->sz + 1 : 1;
    }}
    return sm;
}

int main(){
    ios::sync_with_stdio(0);
    std::srand(time(0));
    Ptr itr[10100]{}; // iterator
    loop(_,input()){
        Ptr root = nullptr;
        int n = input();
        Vec srt;
        loop(_,n){
            int vl = input();
            srt.emplace_back(vl);
            Ptr nw = new Node(vl);
            itr[vl] = insert_at (root, nw, inf);
        }
        std::vector<pii> ans;
        rep(i,1,n+1){
            int r = pos_of(itr[i]) + 1;
            while (r != 1){
                int l = r & 1;
                int m = (l + r) / 2;
                ans.emplace_back(i + l, i + r);
                rotate(root, l, m, r);
                r = m;
            }
            Ptr tmp = nullptr;
            split (root, tmp, root, 1);
        }
        cout << ans.size() << '\n';
        for (auto p : ans){
            cout << p.fi << ' ' << p.se-1 << '\n';
        }
    }
}
