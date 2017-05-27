// spoj : SUMSUMS
// by krist7599555

#include <bits/extc++.h>
#define rep(i,k,n) for(int i=(k);i!=(n);++i)
#define all(x) (x).begin(),(x).end()
using namespace std;
typedef long long lli;

const lli mxsz = 2;
const lli mod  = 98765431;

struct Mat {
	
	lli (*c)[mxsz];
	
	Mat(lli _ini = 0): c(new lli[mxsz][mxsz]{}){ rep(i,0,mxsz) c[i][i] = _ini;}
	Mat(const Mat& m): c(new lli[mxsz][mxsz]{}){ std::copy_n (m.c[0], mxsz * mxsz, c[0]); }
	Mat(const initializer_list<lli>& l): c(new lli[mxsz][mxsz]) { std::copy(all(l),c[0]); }
	~Mat(){delete[] c;}
	
	void operator= (const Mat& m){
		std::copy_n (m.c[0], mxsz * mxsz, c[0]);
	}
	inline lli* operator [](int i){
		return c[i];
	}	
	inline const lli* operator [](int i) const {
		return c[i];
	}
	
	friend Mat operator* (const Mat& a, const Mat& b){
		Mat res;
		rep(i,0,mxsz){
		rep(j,0,mxsz){
		rep(k,0,mxsz){
			res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
		}}}
		return res;
	}

	friend Mat operator^ (Mat num, lli expo){
		Mat res(1);
		while (expo){
			if (expo & 1)
			res = res * num;
			num = num * num;
			expo >>= 1;
		}
		return res;
	}
	friend ostream& operator << (ostream& o, const Mat& m){
		rep(i,0,mxsz){
		rep(j,0,mxsz){
			o << m[i][j] << " \n"[j+1==mxsz];
		}}
		return o;
	}
};



int main(){

	ios::sync_with_stdio(0);
	lli n,k;
	cin >> n >> k;
	vector<lli> v(n);
	
	rep(i,0,n) 
		cin >> v[i];
	
	lli sum = accumulate(all(v),0LL);
	Mat tmp = Mat{0,n-1,1,n-2} ^ k;
	
	for (lli i : v){
		cout << (i * tmp[0][0] % mod + (sum - i) % mod * tmp[1][0] % mod) % mod << '\n';
	}

}
