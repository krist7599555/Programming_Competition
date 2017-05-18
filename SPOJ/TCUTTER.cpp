// spoj : TCUTTER
// krist7599555
// http://contest.mff.cuni.cz/old/archive/ceeu1996/index.html

#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) int((x).size())
#define fi first
#define se second
#define cin() ({int _; cin >> _; _;})
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
typedef long long lli;
typedef std::vector<int> Vec;
typedef std::pair<int,int> pii;

struct Data {
	int x[2];
	int y[2];
};

const int mxn = 512;
bool _vist[mxn][mxn];
#define  _set(_i,_j) void(_vist[_i][_j] = true)
#define _test(_i,_j) bool(_vist[_i][_j])

int cmpss (vector<Data>& in, int(Data::*var)[2]){
	Vec cmpss(in.size()*2);
	rep(i,0u,in.size()){
		cmpss[i<<1]   = (in[i].*var)[0];
		cmpss[i<<1|1] = (in[i].*var)[1];
	}
	sort(ALL(cmpss));
	cmpss.erase(unique(ALL(cmpss)),cmpss.end());
	
	rep(i,0,SZ(in)){
	rep(k,0,2){
		int& val = (in[i].*var)[k];
		val = distance (cmpss.begin(), lower_bound (ALL(cmpss), val)) * 2 + 1;
	}}
	return cmpss.size() * 2 + 1; // [0,en)
}

void bfs_fill (int _r, int _c, int _mxr, int _mxc, bool _jump){
	
	#define can_move(i,j) (-1 < i and i < _mxr and -1 < j and j < _mxc)
	#define push_queue(i,j) assert(not _test(i,j)),_set(i,j),q.emplace(i,j)
	static queue<pii> q;
	static int x[] = {-1,0,1,0};
	static int y[] = {0,-1,0,1};
	
	push_queue(_r,_c);
	while (not q.empty()){
		int _i,_j; 
		tie(_i,_j) = q.front(); q.pop();
		rep(k,0,4){
			int i = _i + x[k];
			int j = _j + y[k];
			if (can_move(i,j)){
				if (not _test(i,j)){
					push_queue(i,j);
				}else if(_jump){
					i += x[k]; 
					j += y[k];
					if (can_move(i,j) and not _test(i,j)){
						push_queue(i,j);
	}}}}}
	
}

int main(){
	
    cin.sync_with_stdio(0);
    cin.tie(0);
    int n;
	vector<Data> in;
    while (cin >> n, n != 0){
		
		in.resize(n);
		for (Data& d : in)
			cin >> d.x[0] >> d.y[0] >> d.x[1] >> d.y[1];
			
		int szx = cmpss (in, &Data::x);
		int szy = cmpss (in, &Data::y);
		std::fill_n (*_vist, mxn * mxn, false);
		
		for (const Data d : in){
			int s,t;
			if (d.x[0] == d.x[1]){
				tie(s,t) = minmax(d.y[0],d.y[1]);
				while (s <= t) _set (d.x[0], s++);
			}else{
				tie(s,t) = minmax(d.x[0],d.x[1]);
				while (s <= t) _set (s++, d.y[0]);
			}
		}
		bfs_fill (0,0,szx,szy,false);
		
		int cnt = 0;
		rep(i,0,szx){
		rep(j,0,szy){
			if (not _test(i,j)){
				bfs_fill (i,j,szx,szy,true);
				cnt++;
			}
		}}
		printf("%d\n",cnt);
	}
	return 0;
}
