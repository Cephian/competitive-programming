#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef pair<int,int> pii;

const int N = 1e4+5;
int d[N], v[N];
set<pii> Q;

int solve(bool f = true) {
	pii p = *Q.rbegin();
	Q.erase(p);
	while(p.first --> f) {
		int v = solve();
		cout << p.second << " " << v << "\n";
	}
	return p.second;
}

int main() {
	fio;	
	int n,m;
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int a,b;
		cin >> a >> b;
		++d[a], ++d[b];
	}
	for(int i = 0; i < n; ++i)
		v[i] = i;
	sort(v,v+n,[](int a, int b) {
		return d[a] < d[b];
	});
	int left = n-2, changed = 0;
	for(int i = 0; i < n; ++i) {
		int j = v[i], add = min(left,d[j]-1);
		left -= add;
		if(d[j] != 1+add) ++changed;
		d[j] = 1+add;
	}
	cout << changed << "\n" << n << " " << (n-1) << "\n";
	for(int i = 0; i < n; ++i)
		Q.insert(pii(d[i],i));
	solve(false);
}