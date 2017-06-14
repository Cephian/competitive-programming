#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//query polynomial hash of substring [l,r] of s
struct str_hash {
	vector<ll> h,bp;
	const static ll BASE=37, MOD=1e9+9;
	str_hash(){}
	str_hash(const string& s):h(s.size()+1),bp(s.size()+1,1) {
		for(int i = 0; i < s.size(); ++i) {
			h[i+1] = (h[i]*BASE + s[i]-'a'+1)%MOD;
			bp[i+1] = (bp[i]*BASE)%MOD;
		}
	}

	//inclusive range hash
	ll hash(int i, int j) {
		ll r = (h[j+1] - h[i]*bp[j-i+1])%MOD;
		return (r<0)?r+MOD:r;
	}
};

int main() {
	str_hash S("abcabd");
	cout << S.hash(0,1) == S.hash(3,4) << endl; // output: 1
	return 0;
}