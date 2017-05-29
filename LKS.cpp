#include <bits/extc++.h>
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
using namespace std;
typedef std::pair<int,int> pii;
typedef std::vector<int> Vec;
typedef std::vector<pii> DP_type;

int N,K;
std::vector<pii> vec;
 
DP_type solve (const int pos){
	
  DP_type res;
	
  if (pos == -1){
		res.emplace_back(0,0);
    
	}else{
		int wei = vec[pos].fi;
		int val = vec[pos].se; 
    
		res = move(solve(pos-1));
		res.resize(res.size() * 2);
		auto mid = res.begin() + res.size() / 2;
		
		transform (res.begin(), mid, mid, [=](const pii& p){
			return pii (p.fi + wei, p.se + val);
		});
		inplace_merge (res.begin(), mid, res.end());
		while (res.back().fi > K) 
      res.pop_back();
		res.erase (res.begin(), 
			unique(res.rbegin(),res.rend(),
				[](pii& a, pii& b){ return a.fi == b.fi; })
				.base()
		);
	}
	return res;
}
 
int main(){
	cin.sync_with_stdio(0);
	cin >> K >> N;
	vec.resize(N);
	for (int i = 0; i != N; ++i) 
		cin >> vec[i].se >> vec[i].fi;
	DP_type m = solve(N-1);
	cout << accumulate(all(m),0,[](int i, const pii& p){ return max(i,p.se); });
}
