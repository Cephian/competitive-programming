#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll n,b;

ll test(ll x) {
	return max(0LL,x*(n-x*b));
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> b;
		cout << max(test(n/(2*b)) , test((n+2*b-1)/(2*b))) << "\n";
	}
} 