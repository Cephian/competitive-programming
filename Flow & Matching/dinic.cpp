#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

template <class X>
struct dinic {
	struct edge {
		int u, v;
		X cap, flow;
		edge() {}
		edge(int u, int v, X cap): u(u), v(v), cap(cap), flow(0) {}
	};

	int N;
	vector<edge> E;
	vector<vector<int>> g;
	vector<int> d, pt;

	dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

	void add_edge(int u, int v, X cap) {
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

	X dfs(int u, int T, X flow = -1) {
		if(u == T || !flow) return flow;
		for(int &i = pt[u]; i < g[u].size(); ++i) {
			edge &e = E[g[u][i]];
			edge &oe = E[g[u][i]^1];
			if(d[e.v] == d[e.u] + 1) {
				X amt = e.cap - e.flow;
				if(flow != -1 && amt > flow) amt = flow;
				if(X pushed = dfs(e.v, T, amt)) {
					e.flow += pushed;
					oe.flow -= pushed;
					return pushed;
				}
			}
		}
		return 0;
	}

	X flow(int S, int T) {
		X tot = 0;
		while(bfs(S, T)) {
			// if using fp arithmetic, limit this to N passes explicitly
			fill(pt.begin(), pt.end(), 0);
			while(X flow = dfs(S, T))
				tot += flow;
		}
		return tot;
	}
};