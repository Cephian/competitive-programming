#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct str_hash {
	vector<int> h1,h2;
	static vector<int> b1,b2;
	constexpr static int B = 31, M1 = 1e9+7, M2 = 1e9+9;
	str_hash(const string& s) {
		h1.resize(s.size()+1,0);
		h2.resize(s.size()+1,0);
		while(b1.size() <= s.size()) {
			b1.push_back(1LL * b1.back() * B % M1);
			b2.push_back(1LL * b2.back() * B % M2);
		}
		for(int i = 0; i < s.size(); ++i) {
			h1[i+1] = (1LL * h1[i] * B + s[i]) % M1;
			h2[i+1] = (1LL * h2[i] * B + s[i]) % M2;
 		}
	}

	ll hash(int i, int j) const {
		ll a1 = (h1[j+1] - 1LL * h1[i] * b1[j-i+1]) % M1;
		ll a2 = (h2[j+1] - 1LL * h2[i] * b2[j-i+1]) % M2;
		if(a1 < 0) a1 += M1;
		if(a2 < 0) a2 += M2;
		return a1 ^ (a2<<32);
	}
};
vector<int> str_hash::b1={1}, str_hash::b2={1};

bool eq(const string& s, int a, int b, int c, int d) {
	for(int k = 0; k <= b-a; ++k)
		if(s[a+k] != s[c+k])
			return false;
	return true;
}

string t[15];
pair<vector<int>,int> ov[15];
int n,s;

int main() {	
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >> n >> s;
	for(int i = 0, sz; i < s; ++i) {
		cin >> t[i], sz = t[i].size();
		str_hash S(t[i]);
		ov[i].second = i;
		for(int j = sz-1; j >= max(1,2*sz-n); --j)
			if(S.hash(0,j-1) == S.hash(sz-j,sz-1))
				ov[i].first.push_back(j);
	}
	sort(ov,ov+s);
	for(int i = 0; i < s; ++i)
		cout << t[ov[i].second] << "\n";
}