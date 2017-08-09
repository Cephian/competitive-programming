#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct str_hash {
	vector<ll> h,b;
	constexpr static ll B = 37;
	str_hash(const string& s):h(s.size()+1),b(s.size()+1,1) {
		for(int i = 0; i < s.size(); ++i) {
			h[i+1] = h[i]*B+s[i]-'a'+1;
			b[i+1] = b[i]*B;
		}
	}

	//inclusive range hash
	ll hash(int l, int r) {
		return h[r+1] - h[l]*b[r-l+1];
	}
};

const int N = 1e5+5;
int dp[N][33];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n,m,x;
	string s,t;
	cin >> n >> s >> m >> t >> x;
	str_hash S(s),T(t);
	for(int i = 0; i <= n; ++i) {
		for(int r = 0; r <= x; ++r) {
			if(dp[i][r] == m) {
				cout << "YES\n";
				return 0;
			}
			dp[i+1][r] = max(dp[i+1][r],dp[i][r]);
			int lo = 0, hi = min(t.size()-dp[i][r],s.size()-i);
			int j = dp[i][r];
			if(j == m || i == n || s[i] != t[j]) continue;
			while(hi-lo>1) {
				int md = (lo+hi)/2;
				if(S.hash(i,i+md) == T.hash(j,j+md)) lo = md;
				else hi = md;
			}
			dp[i+hi][r+1] = max(dp[i+hi][r+1],j+hi);
		}
	}
	cout << "NO\n";
}