#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int r,c,g[105][105],mxr[105]={},mxc[105]={};
unordered_set<int> S;
struct hopcroft_karp {
	int N,M;

	vector<vector<int>> E;
	vector<int> dist,match,Q;
	hopcroft_karp(int n, int m):N(n),M(m),E(N),dist(N+M),match(N+M,-1),Q(N+M){}

	inline void add_edge(int i, int j) {E[i].push_back(j);}

	bool bfs() {
		fill(&dist[0],&dist[0]+N+M,-1);
		int qf = 0, qb = 0, u;
		bool ok = false;
		for(int i = 0; i < N; ++i)
			if(match[i] == -1)
				Q[qb++] = i, dist[i] = 0;
		while(qf != qb) {
			if((u = Q[qf++]) < N) {
				for(int v : E[u])
					if(dist[N+v] == -1)
						dist[Q[qb++] = N+v] = dist[u] + 1;
			} else {
				if(match[u] == -1) ok = true;
				else if(dist[match[u]] == -1)
					dist[Q[qb++] = match[u]] = dist[u] + 1;
			}
		}
		return ok;
	}

	bool dfs(int u) {
		for(int &i = Q[u]; i < E[u].size(); ++i) {
			int v = N+E[u][i];
			if(dist[v] == dist[u]+1 && (match[v] == -1 || (dist[match[v]] == dist[v]+1 && dfs(match[v])))) {
				match[v] = u, match[u] = v-N;
				return true;
			}
		}
		return false;
	}

	int solve() {
		int ans = 0;
		while(bfs()) {
			fill(&Q[0],&Q[0]+N,0);
			for(int i = 0; i < N; ++i)
				if(match[i] == -1 && dfs(i))
					++ans;
		}
		return ans;
	}
};

int main() {	
	scanf("%d%d",&r,&c);
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j) {
			scanf("%d",g[i]+j);
			mxr[i] = max(mxr[i],g[i][j]);
			mxc[j] = max(mxc[j],g[i][j]);
			if(g[i][j]) S.insert(g[i][j]);
		}
	}
	ll ans = 0;
	for(int h : S) {
		int mr=0,mc=0,tot=0;
		hopcroft_karp HK(r,c);
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j) {
				if(g[i][j] == h)
					++tot;
				if(g[i][j] != 0 && mxr[i] == h && mxc[j] == h)
					HK.add_edge(i,j);
			}
		for(int i = 0; i < r; ++i) mr += mxr[i] == h;
		for(int j = 0; j < c; ++j) mc += mxc[j] == h;
		ans += 1LL * (tot - mr - mc + HK.solve()) * (h - 1);
	}
	printf("%lld\n",ans);
}