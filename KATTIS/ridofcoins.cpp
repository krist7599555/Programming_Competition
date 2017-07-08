// https://open.kattis.com/problems/ridofcoins
// greedy
#include <bits/stdc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
using namespace std;
typedef long long lli;
typedef std::vector<int> Vec;

int main(){
	const int v = 0;
	const Vec _5_10_25 = {5, 10, 25};
	lli c[30]{}; // const
	lli u[30]{}; // used
	lli ans  = 0;
	lli best = -1;
	cin >> c[v] >> c[1] >> c[5] >> c[10] >> c[25];

	{// 'rem' case
		int rem = c[v] % 5;
		if (rem > c[1]) return puts("Impossible"), 0;
		c[1]  -= rem;
		c[1] = c[1] / 5 * 5; // every thing will be (mod 5)
		c[v]  -= rem;
		ans += rem;
		assert (c[1] % 5 == 0);
	}
	
	auto need   = [&]{ return c[v] - u[v]; };
	auto greedy = [&](int coin){
		int mn = std::min(need() / coin * coin, (c[coin] - u[coin]) * coin) / coin;
		u[v] += mn * coin;
		u[coin] += mn;
	};
	auto isOK = [&]{ // update ANS
		if(not need()) best = std::max(best,(u[1] + u[5] + u[10] + u[25] + ans)); 
	};
	auto used = [&](int coin,int many){
		u[v] += coin * many;
		u[coin] += many;
	};
	auto free = [&](int coin){ u[v] -= coin * u[coin], u[coin] = 0; };
	auto rmov = [&](int _v,int _t){ loop(_,_t) if(u[_v]) used(_v,-1); };

	
	rep(i,0,5){ // [1]
		free(1);  
		greedy(1); 
		rmov(1, i * 5);
		rep(j,0,5){ // [5]
		rep(k,0,3){ // [10]
			Vec vec{5,10,25};
			do{
				std::for_each(all(_5_10_25),free);
				std::for_each(all(_5_10_25),greedy);
				rmov(5 ,j);
				rmov(10,k);
				std::for_each(all(vec),greedy);
				isOK();
			}while(next_permutation(all(vec)));
		}}
		
	}
	puts (~best ? to_string(best).c_str() : "Impossible");
}
