https://training.kattis.com/problems/base2palindrome
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long lli;
typedef std::string Str;

struct HalfPalin{
	
	uint value;
	bool merge;
	HalfPalin (uint v, bool m): value(v), merge(m) {}
	
	Str to_string() const {
		Str  s;
		uint hv = value;
		while (hv){
			s += '0' + (hv & 1);
			hv >>= 1;
		}
		return string(s.rbegin(),s.rend() - merge) + s;
	}
	static HalfPalin kth_parlin (uint k){
		for (uint i = 1; ; i <<= 1){
			for (bool m : {true, false}){
			for (uint j = 0; j != i; ++j){ 
				if(!k--) return HalfPalin(i|j,m);
	}}}}
};



int main(){
	int v; cin >> v;
	cout << std::bitset<64>(HalfPalin::kth_parlin(v-1).to_string()).to_ulong();
}
