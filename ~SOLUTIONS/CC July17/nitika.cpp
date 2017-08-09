#include <bits/stdc++.h>
#define pb push_back
using namespace std;
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	string s;
	getline(cin,s);
	while(getline(cin,s)) {
		stringstream ss(s);
		vector <string> v;
		while(ss >> s)
			v.pb(s);
		for(int i = 0; i < v.size(); ++i) {
			if(i+1 != v.size()) {
				cout << (char)toupper(v[i][0]) << ". ";
			} else {
				for(int j = 0; j < v[i].size(); ++j) {
					if(j) cout << (char)tolower(v[i][j]);
					else cout << (char)toupper(v[i][j]);
				}
				cout << "\n";
			}
		}
	}
} 