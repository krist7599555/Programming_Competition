// spoj : CVJETICI
// by krist7599555

#include <bits/stdc++.h>
#include <iostream>
#define loop(i,n) for(int i = n; i--;)
using namespace std;

const int n = 1 << 17;

int del[n]; // already used, delete it
int seg[n * 2];

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int q;
  cin >> q;
  loop(_,q){
    int l, r;
    int ans = 0;
    cin >> l >> r;
    for (int x : {l, r}){
      int sm = -del[x];
      for (int _x = x + n; _x != 0; _x >>= 1){
        sm += seg[_x];
      }
      ans += sm;
      del[x] += sm;
    }
    for (l += n + 1, r += n; l != r; l >>= 1, r >>= 1){
      if (l&1) seg[l++]++;
      if (r&1) seg[--r]++;
    }
    cout << ans << '\n';
  }
}
     
