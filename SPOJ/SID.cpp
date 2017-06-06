#include <bits/extc++.h>
#include <iostream>
#include <cstring>
#define fi first
#define se second
using namespace std;

#include <unordered_map>
#include <tr1/unordered_map>
#include <ext/hash_map>

std::unordered_multimap<int,int> 			      m; // AC
//~ std::unordered_map<int,std::queue<int>> m; // TLE
//~ std::tr1::unordered_multimap<int,int> 	m; // WA
//~ __gnu_cxx::hash_multimap<int,int> 		  m; // WA
//~ __gnu_pbds::gp_hash_table<int,std::queue<int>> m; // TLE
//~ __gnu_pbds::cc_hash_table<int,std::queue<int>> m; // TLE

int main(){
	
	ios::sync_with_stdio(0); cin.tie(0);
	int n,q;
	cin >> n >> q;
	int cnt = 0;
	
	while (n--){
		int v; cin >> v;
		m.insert({v,++cnt});
	}
	auto last_bef = [](auto l, auto r){ while (next(l) != r) ++l; return l; };	
	while (q--){
		int  v;
		char c;
		cin >> c >> v;
		auto it = m.equal_range(v);
	
		if (c == 'S'){
			if (it.fi == it.se) cout << "NONE\n";
			else cout << last_bef(it.fi,it.se)->se << '\n';
		}
		if (c == 'I'){
			cout << (m.insert({v,++cnt}), cnt) << '\n';
		}
		if (c == 'D'){
			if (it.fi == it.se) cout << "NONE\n";
			else{
				it.fi = last_bef(it.fi,it.se);
				cout << it.fi->se << '\n';
				m.erase(it.fi);
			}
		}
	}
  return 0;
}
