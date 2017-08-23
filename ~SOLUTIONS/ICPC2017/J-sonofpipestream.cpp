#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

const double EPS = 1e-9;

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
		int passes = 0;
		while(bfs(S, T)) {
			if(++passes > 2*N) break;
			fill(pt.begin(),pt.end(),0);
			while(X flow = dfs(S, T))
				tot += flow;
		}
		return tot;
	}

	void reset() { for(edge &e : E) e.flow = 0; }
};

vector<pii> E;
map<pii,double> F,W;

int main() {	
	int n,p;
	double v,a;
	scanf("%d%d%lf%lf",&n,&p,&v,&a);
	dinic<int> d1(n+1);
	dinic<double> d2(n+1),d3(n+1);
	d1.add_edge(0,1,1e8);
	d1.add_edge(0,2,1e8);
	while(p--) {
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		E.emplace_back(u,v);
		d1.add_edge(u,v,c), d1.add_edge(v,u,c);
		d2.add_edge(u,v,c), d2.add_edge(v,u,c);
	}
	int max_flow = d1.flow(0,3);
	d1.reset();
	int ub = d1.flow(1,3);
	d1.reset();
	int lb = max_flow-d1.flow(2,3);

	double opt = a*max_flow;
	if(opt > ub) opt = ub;
	if(opt < lb) opt = lb;
	d2.add_edge(0,1,opt);
	d2.add_edge(0,2,max_flow-opt);
	d2.flow(0,3);
	for(const auto &e : d2.E) {
		if(e.cap == 0 && e.flow != 0 ) continue;
		d3.add_edge(e.u,e.v,e.flow);
		pii p(e.u,e.v);
		if(e.v > e.u) W[p] += e.flow;
		else swap(p.first,p.second), W[p] -= e.flow;
	}
	d3.flow(1,3);
	for(const auto &e : d3.E) {
		if(e.cap == 0) continue;
		pii p(e.u,e.v);
		if(e.v > e.u) {
			W[p] -= e.flow;
			F[p] = e.flow;
		} else {
			swap(p.first,p.second);
			W[p] += e.flow;
			F[p] = -e.flow;
		}
	}
	for(pii &p : E)
		printf("%.9lf %.9lf\n",F[p]/v,W[p]);
	printf("%.9lf\n",pow(opt/v,a) * pow(max_flow-opt,1-a));
}