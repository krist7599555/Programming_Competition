// spoj : BLOPER
// by krist7599555

#include <bits/extc++.h>
#include <iostream>
using namespace std;

int main(){
	
	int n, dest;
	cin >> n >> dest;
	
	int sn = -n * (n + 1) / 2;
	sn += 2; // 1 always be positive
	
	std::stack<int> stk;
	
	for (int v = n; v >= 2; --v){
		if (sn + 2 * v <= dest){
			stk.push(v);
			sn += 2 * v;
		}else
			stk.push(-v);
	}
  
	if (sn == dest){
		cout << 1;
		while (not stk.empty()){
			cout << std::showpos << stk.top(); 
			stk.pop();
		}
	}else puts("Impossible");
}
