//find strongly connected components in a graph
//scc ids are indexed topologically, e.g.  edge a -> b implies scc[a] <= scc[b]
struct scc {
	int sz=0; //the number of sccs
	vector<int> id; //id[v] is the scc id of v
	int N,ls=0;
	vector<int> L;
	vector<vector<int>> G,R;

	void init(int n) { N = n, G.resize(N), R.resize(N), id.resize(N), L.resize(N); }

	scc(){}
	scc(int n){init(n);}

	void dfs1(int v) {
		if(id[v]) return;
		id[v] = 1;
		for(auto u : G[v])
			dfs1(u);
		L[ls++] = v;
	}

	void dfs2(int v, int r) {
		if(~id[v]) return;
		id[v] = r;
		for(int u : R[v])
			dfs2(u,r);
	}

	void add_edge(int u, int v) {
		G[u].push_back(v), R[v].push_back(u);
	}

	//calculate the strongly connected components
	void calc() {
		for(int v = 0; v < N; ++v)
			dfs1(v);
		fill(id.begin(),id.end(),-1);
		for(int i = N-1; i >= 0; --i) {
			if(id[L[i]] == -1)
				dfs2(L[i],sz++);
		}
	}

	//get the digraph of sccs, call AFTER calc
	//remember that indices are ordered topologically
	vector<vector<int>> scc_digraph() {
		vector<vector<int>> B(N);
		for(int u = 0; u < N; ++u)
			for(int v : G[u])
				if(id[u] != id[v])
					B[id[u]].push_back(id[v]);
		for(int i = 0; i < sz; ++i) {
			sort(B[i].begin(),B[i].end());
			B[i].erase(unique(B[i].begin(),B[i].end()),B[i].end());
		}
		return B;
	}
};