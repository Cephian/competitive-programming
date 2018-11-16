// init with hopcroft_karp(left size, right size)
// add_edge(i,j) adds edge from i-th in left to j-th in right (0-indexed)
// solve() returns size of matching, i-th in left is matched to E[i]-th in right
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