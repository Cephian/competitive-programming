#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

const int N = 5e5+5;
int m,n;
pll A[N],B[N];
vector<pll> C,D;
ll ans = 0;

ll area(int i, int j) {
	if(D[j].second < C[i].second || D[j].first < C[i].first) return 0;
	return (D[j].second - C[i].second) * (D[j].first - C[i].first);
}

void solve(int i, int j, int l, int r) {
	if(j < i) return;
	int k = (i+j)/2, best = r;
	for(int m = r; m >= l; --m)
		if(area(k,m) > area(k,best))
			best = m;
	ans = max(ans, area(k,best));
	solve(i,k-1,l,best);
	solve(k+1,j,best,r);
}

int main() {	
	scanf("%d%d",&m,&n);
	for(int i = 0; i < m; ++i)
		scanf("%lld%lld",&A[i].first,&A[i].second);
	for(int i = 0; i < n; ++i)
		scanf("%lld%lld",&B[i].first,&B[i].second);
	sort(A,A+m), sort(B,B+n);
	for(int i = n-1, best = 0; i >= 0; --i) {
		if(B[i].second <= best) continue;
		best = B[i].second;
		D.push_back(B[i]);
	}
	reverse(D.begin(),D.end());
	for(int i = 0, best = 1e9+5; i < m; ++i) {
		if(A[i].second >= best) continue;
		best = A[i].second;
		int lo = -1, hi = D.size();
		while(hi - lo > 1) {
			int md = (lo+hi)/2;
			if(A[i].first <= D[md].first) hi = md;
			else lo = md;
		}
		if(hi != D.size() && D[hi].second >= A[i].second)
			C.push_back(A[i]);
	}
	solve(0,(int)C.size()-1,0,D.size()-1);
	printf("%lld\n",ans);
}