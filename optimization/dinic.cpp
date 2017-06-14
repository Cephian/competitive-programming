#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

struct edge {
	int u, v;
	ll cap, flow;
	edge() {}
	edge(int u, int v, ll cap): u(u), v(v), cap(cap), flow(0) {}
};

struct dinic {
	int N;
	vector<edge> E;
	vector<vector<int>> g;
	vector<int> d, pt;

	dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

	void add_edge(int u, int v, ll cap) {
		if (u == v) return;
		g[u].emplace_back(E.size());
		E.emplace_back(edge(u, v, cap));
		g[v].emplace_back(E.size());
		E.emplace_back(edge(v, u, 0));
	}

	bool bfs(int S, int T) {
		fill(d.begin(), d.end(), N + 1);
		int qf=0,qb=1;
		d[S] = 0;
		pt[0] = S;
		while(qf!=qb) {
			int u = pt[qf++];
			if(u == T) break;
			for(int k: g[u]) {
				edge &e = E[k];
				if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
					d[e.v] = d[e.u] + 1;
					pt[qb++] = e.v;
				}
			}
		}
		return d[T] != N + 1;
	}

	ll dfs(int u, int T, ll flow = -1) {
		if(u == T || !flow) return flow;
		for(int &i = pt[u]; i < g[u].size(); ++i) {
			edge &e = E[g[u][i]];
			edge &oe = E[g[u][i]^1];
			if(d[e.v] == d[e.u] + 1) {
				ll amt = e.cap - e.flow;
				if(flow != -1 && amt > flow) amt = flow;
				if(ll pushed = dfs(e.v, T, amt)) {
					e.flow += pushed;
					oe.flow -= pushed;
					return pushed;
				}
			}
		}
		return 0;
	}

	ll flow(int S, int T) {
		ll tot = 0;
		while(bfs(S, T)) {
			fill(pt.begin(), pt.end(), 0);
			while(ll flow = dfs(S, T))
				tot += flow;
		}
		return tot;
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