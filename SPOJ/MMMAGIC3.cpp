// spoj : MMMAGIC3
// https://bitbucket.org/eightnoteight/spoj-solutions/src thank for this.

#include <bits/extc++.h>
#define rep(i,k,n) for(decltype(n)i=(k);i!=(n);++i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
using namespace std;
typedef std::vector<int> Vec;

map<Vec,Vec> Mickey, Donald;

int main(){
	
	rep(i,1,9){
	rep(j,1,i){
		rep(k,1,9){
			if (i == j or i == k or j == k) continue;
			Vec v = {i,j,k};
			sort(all(v));
			if (not Mickey.count(v)){
				if (not Donald.count(Vec{i,j})){
					Donald[Vec{i,j}] = {k};
					Mickey[v] = Vec{i,j};
				}
				else if (not Donald.count(Vec{j,i})){
					Donald[Vec{j,i}] = {k};
					Mickey[v] = Vec{j,i};
				}
			}
		}}
		//~ rep(i,1,9){ // so currious :?
		//~ rep(j,1,9){
			//~ cout << (Donald.count(Vec{i,j}) ? Donald[Vec{i,j}].front() : 0) << " \n"[j==8];
		//~ }}
		//~ getchar();
	}
	assert (sz(Donald) == 56 and sz(Mickey) == 56);
	
	int m,d; cin >> m >> d;
	while (m--){
		Vec v(3); cin >> v[0] >> v[1] >> v[2]; sort(all(v));
		cout << Mickey[v][0] << ' ' << Mickey[v][1] << '\n';
	}
	while (d--){
		Vec v(2); cin >> v[0] >> v[1];
		cout << Donald[v][0] << '\n';
	}
	
}
