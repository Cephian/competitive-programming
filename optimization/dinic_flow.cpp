#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

struct edge {
	int v;
	ll c=0;
	edge(int v, ll c):v(v),c(c){}
};

struct dinic {
	int V;
	vector<edge> E;
	vvi g;
	vi d,q;

	dinic(int n) {
		g = vvi(V = n);
		d = q = vi(V);
	}

	void add_edge(int u, int v, ll c) {
		if(u == v) return;
		g[u].push_back(E.size());
		E.emplace_back(v,c);
		g[v].push_back(E.size());
		E.emplace_back(u,0);
	}

	bool bfs(int s, int t) {
		fill(d.begin(),d.end(),V);
		q[0] = s;
		int f = d[s] = 0, b = 1;
		while(f != b) {
			int u = q[f++];
			if(d[u] == d[t]) break;
			for(int i : g[u]) {
				edge &e = E[i];
				if(e.c && d[e.v] > d[u]+1) {
					d[e.v] = d[u]+1;
					q[b++] = e.v;
				}
			}
		}
		return d[t] != V;
	}

	ll dfs(int u, int t, ll f = -1) {
		if(u==t || !f) return f;
		for(int &i = q[u]; i<g[u].size(); ++i) {
			edge &e = E[g[u][i]];
			if(d[u]+1 != d[e.v]) continue;
			if(ll s = dfs(e.v,t,(f!=-1 && e.c>f)?f:e.c)) {
				e.c -= s;
				E[g[u][i]^1].c += s;
				return s;
			}
		}
		return 0;
	}

	ll flow(int s, int t) {
		ll ans = 0;
		while(bfs(s,t)) {
			memset(&q[0],0,V * sizeof q[0]);
			while(ll f = dfs(s,t))
				ans += f;
		}
		return ans;
	}
};

// solution to spoj FASTFLOW
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	ll c;
	dinic d(n);
	while(m--) {
		scanf("%d%d%lld",&a,&b,&c);
		d.add_edge(a-1,b-1,c);
		d.add_edge(b-1,a-1,c);
	}
	printf("%lld\n",d.flow(0,n-1));
	return 0;
}