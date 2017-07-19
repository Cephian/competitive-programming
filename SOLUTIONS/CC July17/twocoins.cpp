#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
 
const int N = 1e5+5;
vvi T;
 
void proc(int u, int v) {
	T[v].erase(remove(T[v].begin(),T[v].end(),u),T[v].end());
	for(auto w : T[v])
		proc(v,w);
}
 
constexpr ll INF = 1LL<<32;
ll dp[N][3][3];
//v is the current vert
//a how many above parent to get to coined, or 2 if too many
//d is how many away from forced place, d = 2 means not needed
ll get(int v, int a, int d) {
	ll &A = dp[v][a][d];
	if(A != -1) return A;
	A = INF;
	//place type 1: shift one from above
	if(a != 2) {
		ll s = 1;
		for(int w : T[v])
			s += get(w,0,2);
		A = min(A,s);
	}
	//place type 2: we need to shift from below
	if(T[v].size() > 0) {
		ll s = 1, mn = INF;
		for(int w : T[v]) {
			s += get(w,0,2);
			mn = min(mn,get(w,0,1)-get(w,0,2));
		}
		s += mn;
		A = min(A,s);
	}
 
	//skip type 1: shift one from above, one from below
	if(d > 0 && a == 0 && T[v].size() > 0) {
		ll s = 0, mn = INF;
		for(int w : T[v]) {
			s += get(w,min(2,a+1),2);
			mn = min(mn,get(w,min(2,a+1),0)-get(w,min(2,a+1),2));
		}
		s += mn;
		A = min(A,s);
	}
	//skip type 2: shift two from below
	if(d > 0 && T[v].size() > 1) {
		ll s = 0, m1 = INF, m2 = INF;
		for(int w : T[v]) {
			ll val = get(w,min(2,a+1),2);
			s += val;
			val = get(w,min(2,a+1),0)-val;
			if(val <= m1) m2 = m1, m1 = val;
			else if(val < m2) m2 = val;
		}
		s += m1+m2;
		A = min(A,s);
	}
	return A;
}
 
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n;
		scanf("%d",&n);
		if(n == 1) {
			printf("-1\n");
			continue;
		}
		T = vvi(n);
		for(int i = 1; i < n; ++i) {
			int u,v;
			scanf("%d%d",&u,&v),--u,--v;
			T[u].pb(v);
			T[v].pb(u);
		}
 
		proc(-1,0);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < 3; ++j)
				for(int k = 0; k < 3; ++k)
					dp[i][j][k] = -1;
		printf("%lld\n",get(0,2,2));
	}
} 