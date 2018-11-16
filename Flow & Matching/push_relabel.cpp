// NEEDS WORK: still slow on SPOJ for some reason??
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

struct edge {
	int v;
	ll c;
	edge(int v, ll c):v(v),c(c){}
};

struct push_relabel {
	int V;
	vector<edge> E;
	vector<vector<int>> g;
	vector<int> label,Q,A;
	vector<ll> excess;
	vector<bool> active;
	int qf=0,qb=0;

	push_relabel(int n) {
		g.resize(V=n);
		label = Q = A = vector<int>(V);
		excess.resize(V);
		active.resize(V);
	}

	void add_edge(int u, int v, ll c) {
		if(u==v) return;
		g[u].push_back(E.size());
		E.push_back(edge(v,c));
		g[v].push_back(E.size());
		E.push_back(edge(u,0));
	}

	void gap(int k) {
		for(int i = 0; i < V; ++i) {
			if(label[i] < k) continue;
			--A[label[i]];
			label[i] = max(label[i],V+1);
			++A[label[i]];
			activate(i);
		}
	}

	void activate(int u) {
		if(active[u]) return;
		active[u] = true;
		Q[qb++] = u;
		if(qb == V) qb = 0;
	}

	void push(int i) {
		edge &e = E[i], &r = E[i^1];
		ll a = min(excess[r.v],e.c);
		if(!a) return;
		e.c -= a;
		r.c += a;
		excess[e.v] += a;
		excess[r.v] -= a;
		activate(e.v);
	}

	void relabel(int u) {
		--A[label[u]];
		label[u] = 2*V;
		for(int i : g[u])
			if(E[i].c)
				label[u] = min(label[u],1+label[E[i].v]);
		++A[label[u]];
		activate(u);
	}

	void discharge(int u) {
		for(int i = 0; excess[u] && i < g[u].size(); ++i) {
			edge &e = E[g[u][i]];
			if(label[u] > label[e.v])
				push(g[u][i]);
		}
		if(excess[u]) {
			if(A[label[u]] == 1) gap(label[u]);
			else relabel(u);
		}
	}

	ll flow(int s, int t) {
		active[s] = active[t] = true;
		label[s] = V;
		A[V] = 1;
		A[0] = V-1;
		for(int i : g[s]) {
			excess[s] += E[i].c;
			push(i);
		}
		while(qf != qb) {
			int u = Q[qf++];
			if(qf == V) qf = 0;
			active[u] = false;
			discharge(u);
		}
		return excess[t];
	}
};