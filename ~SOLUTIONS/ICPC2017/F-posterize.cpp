#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int d,k;
ll freq[256];
ll dp[256][256]={};
ll cost_hi[256][256]={}, cost_lo[256][256]={};

ll cost(int i, int j) {
	int k = (i+j)/2;
	return cost_lo[i][k] + cost_hi[k+1][j];
}

int main() {	
	scanf("%d%d",&d,&k);
	while(d--) {
		int r;
		scanf("%d",&r);
		scanf("%lld",freq+r);
	}
	for(int i = 0; i < 256; ++i) {
		for(int j = i; j < 256; ++j) {
			for(int l = i; l <= j; ++l) {
				cost_lo[i][j] += freq[l] * (l - i) * (l - i);
				cost_hi[i][j] += freq[l] * (j - l) * (j - l);
			}
		}
	}
	ll ans = 1LL<<62;
	for(int i = 0; i < 256; ++i)
		dp[i][1] = cost_hi[0][i];
	for(int j = 2; j <= k; ++j) {
		for(int i = 0; i < 256; ++i) {
			dp[i][j] = ans;
			for(int l = 0; l <= i; ++l)
				dp[i][j] = min(dp[i][j], dp[l][j-1] + cost(l,i));
		}
	}
	for(int l = 0; l < 256; ++l)
		ans = min(ans,dp[l][k] + cost_lo[l][255]);
	printf("%lld\n",ans);
}