struct lca {
	void init(int n) { T.resize(N = n); }
	lca(){}
	lca(int n){init(n);}
	int N,ctr=0;
	vector<int> idx,depth;
	vector<vector<int>> table,T;
	static inline int lg(int a) {return 31-__builtin_clz(a);}
	void dfs(int u, int v, int d) {
		idx[v] = ctr;
		depth[v] = d, table[0][ctr++] = v;
		for(int i = 0; i < (int)T[v].size(); ++i)
			if(T[v][i] != u)
				dfs(v,T[v][i],d+1), table[0][ctr++] = v;
	}

	void add_edge(int u, int v) {
		T[u].push_back(v);
		T[v].push_back(u);
	}

	//call build after edges are added
	void build(int root = 0) {
		idx.resize(N), depth.resize(N), table.assign(lg(2*N-1)+1,vector<int>(2*N-1));
		dfs(-1,root,0);
		for(int k = 0; k+1 < (int)table.size(); ++k) {
			for(int i = 0; i < (int)table[k].size(); ++i) {
				int j = min(i+(1<<k),(int)table[k].size()-1);
				table[k+1][i] = (depth[table[k][i]] < depth[table[k][j]])?table[k][i]:table[k][j];
			}
		}
	}

	//lca(u,v)
	inline int query(int u, int v) const {
		u = idx[u], v = idx[v];
		if(v < u) swap(u,v);
		int g = lg(v-u+1);
		u = table[g][u], v = table[g][v+1-(1<<g)];
		return (depth[u] < depth[v])?u:v;
	}

	//unweighted distance between u and v
	inline int dist(int u, int v) {
		return depth[u] + depth[v] - 2*depth[query(u,v)];
	}
};
