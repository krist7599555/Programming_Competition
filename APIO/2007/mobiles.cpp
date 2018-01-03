// APIO 2007 mobiles
#include <bits/stdc++.h>
#define input() (*std::istream_iterator<int>(cin))
#define loop(i,n) for(int i = n; i--;)
#define invaid() std::exit(!puts("-1"))
using namespace std;

struct MnMx {
	int mn, mx;
	MnMx(int a = 0): mn(a), mx(a) {}
	MnMx(int a, int b): mn(a), mx(b) { 
		assert(a <= b); 
		if(mx - mn >= 2) invaid(); // layer not differ more than 1
	}
};

struct Data {
	Data *ml, *mr;
	Data(Data* l = 0, Data* r = 0): ml(l), mr(r) {}
	MnMx solve(int& cnt, int dep = 1) {
		if (!ml && !mr) return MnMx(dep);
		MnMx pl = ml->solve(cnt, dep+1);
		MnMx pr = mr->solve(cnt, dep+1);
		loop(_,2){
			if (pl.mn == pr.mx || pl.mn - 1 == pr.mx) 
				return MnMx(pr.mn, pl.mx);
			std::swap(pl, pr); cnt++;
		}
		invaid();
	}
};

const int mxn = 1e5 + 10;
Data tmp[mxn];

int main(){
	cin.sync_with_stdio(0);
	int n = input();
	for (int i = 1; i <= n; ++i){
		int l = input(); l = ~l ? l : 0;
		int r = input(); r = ~r ? r : 0;
		tmp[i] = Data(tmp + l, tmp + r);
		assert ((!l || l >= i) and (!r || r >= i)); // DAG
	}
	int cnt = 0;
	tmp[1].solve(cnt);
	cout << cnt << endl;
}
