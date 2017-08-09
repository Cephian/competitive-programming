//solved in contest
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
 
const int N = 1e5+5;
int n,m,A[N];
 
vector<int> at[N];
 
int main() {
	scanf("%d%d",&n,&m);
	ll tot_cross = 0;
	ll tot_score = 0;
	for(int i = 0; i < n; ++i) {
		scanf("%d",A+i),--A[i];
		at[A[i]].pb(i);
		if(i) {
			if(A[i-1] < A[i]) tot_score += (A[i]-A[i-1]+m)%m;
			else {
				++tot_cross;
				tot_score += A[i]+1;
			}
		}
	}
 
	ll ans = tot_score;
	for(int x = 1; x < m; ++x) {
		//remove any no longer applicable
		for(int i : at[x-1]) {
			if(i != 0) {
				tot_score += (A[i]-A[i-1]+m)%m-1,--tot_cross;
			}
		}
		//shift crossers
		tot_score -= tot_cross;
		//discover new crossers
		for(int i : at[x-1])
			if(i != n-1) {
				++tot_cross;
			}
		//min ans
		ans = min(ans,tot_score);
	}
	printf("%lld\n",ans);
}