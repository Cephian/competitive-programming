#include <bits/stdc++.h>
using namespace std;

string s,t;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n,m;
	cin >> n >> m >> s >> t;
	int bn = 0x7fffffff,bi = -1;
	for(int i = 0; i+s.size() <= t.size(); ++i) {
		int df = 0;
		for(int j = 0; j < s.size(); ++j)
			df += s[j]!=t[i+j];
		if(df < bn) bn = df, bi = i;
	}
	cout << bn << "\n";
	for(int j = 0; j < s.size(); ++j)
		if(s[j]!=t[bi+j])
			cout << j+1 << " ";
	cout << "\n";
}