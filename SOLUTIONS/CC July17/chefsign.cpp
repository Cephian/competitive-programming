#include <bits/stdc++.h>
using namespace std;
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		int l1=0,l2=0;
		int mx=0;
		for(char c : s) {
			if(c == '<') ++l1,l2=0;
			else if(c=='>') l1=0,++l2;
			mx = max(mx,max(l1,l2));
		}
		cout << 1+mx << "\n";
	}	
}