#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll a,k;
	cin >> a >> k;
	ll l = a/2/(k+1);
	cout << l << " " << l*k << " " << a-l*(k+1) << "\n";
}