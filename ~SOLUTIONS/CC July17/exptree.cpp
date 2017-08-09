#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll pw(ll a, ll b, ll m) {
	if(b==0) return 1;
	if(b&1) return a*pw(a,b-1,m)%m;
	ll t = pw(a,b/2,m);
	return t*t%m;
}
 
ll calc(ll n, ll m) {
	n %= m;
	ll a = n*(n-1)%m;
	ll b = (4*n-6)%m;
	if(b<0) b+=m;
	return a*pw(b,m-2,m)%m;
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		ll n;
		cin >> n;
		cout << calc(n,1e9+7) << " " << calc(n,1e9+9) << "\n";
	}
}