// spoj : MMMAGIC4
// by krist7599555

#include <bits/extc++.h>
#define rep(i,k,n) for(decltype(n)i=(k);i!=(n);++i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
using namespace std;
typedef std::vector<int> Vec;

const int mxn = 27 * 26 * 25;
map<Vec,Vec> Mickey, Donald;

int main(){
	ios::sync_with_stdio(false);
	
	rep(i,1,28){
	rep(j,1,i){
	rep(k,1,j){
	rep(l,1,28){
		Vec v {i,j,k,l}; sort(all(v)); v.erase(unique(all(v)),v.end());
		if (sz(v) == 4 and not Mickey.count(v)){
			Vec perm {i,j,k}; sort(all(perm));
			do{
				if (not Donald.count(perm)){
					Donald[perm] = Vec{l};
					Mickey[v] = perm;
					break;
				}
			}while(next_permutation(all(perm)));
		}
	}}}}

	assert (sz(Donald) == 27 * 26 * 25 and sz(Mickey) == 27 * 26 * 25);
	
	int m,d; cin >> m >> d;
	while (m--){
		Vec v(4); cin >> v[0] >> v[1] >> v[2] >> v[3]; sort(all(v));
		cout << Mickey[v][0] << ' ' << Mickey[v][1] << ' ' << Mickey[v][2] <<'\n';
	}
	while (d--){
		Vec v(3); cin >> v[0] >> v[1] >> v[2];
		cout << Donald[v][0] << '\n';
	}
	
}
