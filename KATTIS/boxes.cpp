// https://open.kattis.com/problems/boxes
// by krist7599555
// preorder tree-traversal
// 1st place :)

#include <bits/stdc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using namespace std;
typedef std::vector<int> Vec;
typedef Vec::iterator It;

const int mxn = 2e5 + 10;
Vec child[mxn];

int st [mxn]{}; // start point
int en [mxn]{}; // end point
int lis[mxn], *p = lis;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    rep(i,1,n+1){
        int pa;
        cin >> pa;
        child[pa].push_back(i);
    }
    std::stack<std::tuple<int,It,It>> stk;
    stk.emplace(*p++ = 0, all(child[0]));
    
    while (not stk.empty()){ // stack optimize
        int id = get<0>(stk.top());
        It& l  = get<1>(stk.top());
        It& r  = get<2>(stk.top());
        if (l == r){
            en[id] = std::distance(lis, p);
            stk.pop();
        }else{
            st[*l] = std::distance(lis, p);
            stk.emplace(*p++ = *l, all(child[*l]));
            l++;
        }
    }
    
    int q;
    cin >> q;
    loop(_,q){
        int sz;
        cin >> sz;
        Vec v(sz);
        rep(i,0,sz){
            cin >> v[i];
        }
        std::sort(all(v),[=](int i, int j){ return st[i] < st[j]; });
        int sm = 0;
        int x  = 0;
        for (int i : v){
            if (x < en[i]){
                sm += en[i] - std::max(st[i], x);
                x = en[i];
        }}
        cout << sm << '\n';
    }
}
