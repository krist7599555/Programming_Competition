// spoj: STC01  
// I'm not solve this with my own
// http://stilwell.is-programmer.com/posts/48016.html

#include <bits/stdc++.h>
#define rep(i,k,n) for(int i=k;i!=n;++i)
typedef std::vector<int> Vec;
using namespace std;

auto minus_min =[](int& a,int& b){
	int mn = min(a,b);
	a -= mn;
	b -= mn;
};

const int mxn  = 1e5 + 5;
const int mxk  = 25;
const int root = 1;

int n,S,K,ans;
int f[mxn][mxk];
int g[mxn][mxk];
Vec conec[mxn];
 
void dfs(int nw,int pa = -1){
    for (int nx : conec[nw]){
		if (nx != pa){
			dfs(nx,nw);
			for(int j=0;j<=K;++j){
				f[nw][j+1] += f[nx][j];
				if(j){
					g[nw][j-1] = min (g[nw][j-1] + g[nx][j], n);
				}
	}}}
    ++f[nw][0];
    int j = f[nw][K]/S + (f[nw][K]%S!=0);
    ans += j;
    g[nw][K] = j * S - f[nw][K];
    f[nw][K] = 0;
    for(int j = K; j>=0; --j){
		minus_min (f[nw][j], g[nw][j]);
		minus_min (f[nw][j], g[nw][j+1]);
    }
    g[nw][0]=0;
}
 
int main(){
	cin.sync_with_stdio(0);
	cin >> n >> S >> K;
    for(int u, v, i = 1; i != n; ++i){
		cin >> u >> v;
		conec[u].push_back(v);
		conec[v].push_back(u);
    }
    dfs(root);
    
    for(int k = 0, j = K; j >= 0; --j){
        k = min(k + g[root][j], n);
        minus_min(k, f[root][j]);
    }
    int k = accumulate (f[root], f[root]+K+1, 0);
    ans += k/S + (k%S!=0);
    cout << ans;
}
