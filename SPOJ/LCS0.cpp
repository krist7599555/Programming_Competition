// spoj : LCS0
// by krist7599555
// http://users.monash.edu/~lloyd/tildeStrings/Alignment/86.IPL.html

#include <bits/stdc++.h>
#include <iostream>
#include <array>
 
#ifndef _K_BITSET_
#define _K_BITSET_
 
#include <vector>
#include <algorithm>
#include <functional>
#include <ostream>
#include <bitset>
#include <cassert>
#include <numeric>
 
class k_bitset {
public:	
	
	typedef long long block_t;
	
	static const block_t lim  = 1ULL << 60;
	static const block_t msk  = lim - 1;
	static const block_t imsk = ~msk;
	
	std::vector<block_t> _b;
	
	k_bitset (int sz = 60, bool b = false): _b(sz/60+1,b?msk:0){}
	k_bitset (const k_bitset& rhs): _b(rhs._b){}
	k_bitset (k_bitset&& rhs): _b(std::move(rhs._b)){}
	~k_bitset(){}
	
	inline void resize (size_t sz){ return _b.resize(sz/60+1); }
	inline size_t size (){ return _b.size () * 60; }
	inline bool  empty (){ return _b.empty(); }
	
	k_bitset& operator= (	   k_bitset&& rhs) = default;
	k_bitset& operator= (const k_bitset&  rhs) = default;
	
	k_bitset& operator += (const k_bitset& rhs){
		std::transform (_b.begin(),_b.end(),rhs._b.begin(),_b.begin(),std::plus <block_t>()); 
		for (auto it = _b.begin(); it != _b.end(); ++it){
			if (it[0] >> 60){
				it[1] += it[0] >> 60;
				it[0] &= msk;
		}}
		return *this;
	}
	k_bitset& operator -= (const k_bitset& rhs){
		std::transform (_b.begin(),_b.end(),rhs._b.begin(),_b.begin(),std::minus<block_t>()); 
		for (auto it = _b.begin(); it != _b.end(); ++it){
			if (it[0] < 0){
				if (next(it) == _b.end()){
					std::cout << "bug found" << '\n';
					assert (false);
					exit(1);
				};
				it[0] += lim;
				it[1] -= 1;
		}}
		return *this;
	}
	k_bitset& operator <<= (const int shif){
		assert (0 <= shif and shif <= 60);
		for (auto rit = _b.rbegin(); rit != _b.rend(); ++rit){
			rit[0] = ((rit[0] << shif) | (next(rit) == _b.rend() ? 0 : (rit[1] >> (60-shif)))) & msk;
		}
		return *this;
	}
	k_bitset& operator >>= (const int shif){
		assert (0 <= shif and shif <= 60);
		for (auto it = _b.begin(); it != _b.end(); ++it){
			it[0] = ((it[0] >> shif) | (next(it) == _b.end() ? 0 : (it[1] >> (60-shif)))) & msk;
		}
		return *this;
	}
	k_bitset& operator &= (const k_bitset& rhs){ std::transform (_b.begin(),_b.end(),rhs._b.begin(),_b.begin(),std::bit_and<block_t>()); return *this; }
	k_bitset& operator |= (const k_bitset& rhs){ std::transform (_b.begin(),_b.end(),rhs._b.begin(),_b.begin(),std::bit_or <block_t>()); return *this; }
	k_bitset& operator ^= (const k_bitset& rhs){ std::transform (_b.begin(),_b.end(),rhs._b.begin(),_b.begin(),std::bit_xor<block_t>()); return *this; }
	k_bitset  operator &  (const k_bitset& rhs){ k_bitset res(*this); res &= rhs; return res; }
	k_bitset  operator |  (const k_bitset& rhs){ k_bitset res(*this); res |= rhs; return res; }
	k_bitset  operator ^  (const k_bitset& rhs){ k_bitset res(*this); res ^= rhs; return res; }
	k_bitset  operator +  (const k_bitset& rhs){ k_bitset res(*this); res += rhs; return res; }
	k_bitset  operator -  (const k_bitset& rhs){ k_bitset res(*this); res -= rhs; return res; }
	k_bitset  operator >> (const int& shif){ k_bitset res(*this); res >>= shif; return res; }
	k_bitset  operator << (const int& shif){ k_bitset res(*this); res <<= shif; return res; }
	
	friend std::ostream& operator << (std::ostream& o, const k_bitset& rhs){
		for (auto rit = rhs._b.rbegin(); rit != rhs._b.rend(); ++rit) o << std::bitset<60>(*rit);
		return o;
	}
	inline bool operator[] (size_t pos){ return _b[pos/60] & 1 << pos % 60; }
	
	inline void toggle(size_t pos){ _b[pos/60] ^=  (1LL << pos % 60); }
	inline void set   (size_t pos){ _b[pos/60] |=  (1LL << pos % 60); }
	inline void free  (size_t pos){ _b[pos/60] &= ~(1LL << pos % 60); }
	
	size_t count (){ 
		return std::accumulate (_b.begin(),_b.end(),0,
			[](int sm, block_t b){return sm + ::__builtin_popcountll(b);}); 
	}
};
 
#endif
 
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
#define fi first
#define se second
using namespace std;
typedef long long lli;
typedef std::pair<int,int> pii;
typedef std::vector<int> Vec;
typedef std::string Str;
typedef k_bitset Bit;
 
int lcs (Str s1, Str s2){
	std::array<Bit,'z'+1> m;
	int len = sz(s1) + 10;
	int top = sz(s1) + 2;
	rep(i,0,sz(s1)){
		m[s1[i]].resize(len);
		m[s1[i]].set(i+1);
	}
 
	Bit a(len);
	for (char c : s2){
		m[c].resize(len);
		m[c].set(top);  // bound top for minus
		a.set(0);       // base case
		Bit x = a | m[c]; // x == all posible can be
		Bit y = x ^ (x - (a << 1)); // y = nearest bit for each bit in j
		// used xor to make difference bit to bit 1
		// come from fen wick trick remove last bit x & x-1
		// but we used for every bit a << 1 but used minus(-) operator to do it faster
		// it is ok to have 00000000 - 00000010 = 11111100 still fine to used own declear minus
		a = x & y; // result of every bit in a jump to nearest one on a | m[c]
		a.free(top); // remove bound if a<<1 > a|m[c]
	}
	return a.count();
}
 
int main(){
	cin.sync_with_stdio(0);
	string s1(51000,'0'), s2(51000,'0');
	cin >> s1 >> s2;
	cout << lcs(s1,s2);
}
