struct lca {
	int N;
	vector<int> idx,depth;
	vector<vector<int> > table;
	void dfs(const vvi &T, int u, int v, int d, int &ctr) {
		idx[v] = ctr;
		depth[v] = d, table[0][ctr++] = v;
		for(int i = 0; i < T[v].size(); ++i)
			if(T[v][i] != u)
				dfs(T,v,T[v][i],d+1,ctr), table[0][ctr++] = v;
	}

	static inline int lg(int a) {return 31-__builtin_clz(a);}

	lca(){}
	lca(const vvi &T, int root = 0):N(T.size()),idx(N),depth(N),table(lg(2*N-1)+1,vector<int>(2*N-1)) {
		int ctr = 0;
		dfs(T,-1,root,0,ctr);
		for(int k = 0; k+1 < table.size(); ++k) {
			for(int i = 0; i < table[k].size(); ++i) {
				int j = min(i+(1<<(k)),(int)table[k].size()-1);
				table[k+1][i] = (depth[table[k][i]] < depth[table[k][j]])?table[k][i]:table[k][j];
			}
		}
	}

	inline int query(int u, int v) const {
		u = idx[u], v = idx[v];
		if(v < u) swap(u,v);
		int g = lg(v-u+1);
		u = table[g][u], v = table[g][v+1-(1<<g)];
		return (depth[u] < depth[v])?u:v;
	}

	//unweighted distance between u and v
	inline int dist(int u, int v) {
		return depth[u]+depth[v]-2*depth[query(u,v)];
	}
};