//find bridge edges in a connected graph
struct find_bridge {
	//will contain the bridges in (u,v) pairs
	vector<pii> ans_edges;
	//will contain the bridges in indices by insertion order
	vector<int> ans_indices;

	int c=0,ctr=0;
	vector<vector<pii>> G;
	vector<bool> vis;
	vector<int> reach,lab;
	void init(int n) {
		G.resize(n);
		vis.resize(n);
		lab.resize(n);
		reach.resize(n);
	}

	find_bridge(){}
	find_bridge(int n){init(n);}

	void add_edge(int u, int v) {
		G[u].emplace_back(v,c);
		G[v].emplace_back(u,c++);
	}

	//calculate answers and store in ans_edges and ans_indices
	//ignore the return value
	int calc(int f = -1, int v = 0) {
		vis[v] = 1, reach[v] = lab[v] = ctr++;
		for(auto &p : G[v]) {
			int w = p.first, i = p.second;
			if(w == f) continue;
			if(!vis[w] && calc(v,w) > lab[v])
				ans_edges.emplace_back(v,w), ans_indices.push_back(i); //found bridge (v,w)
			reach[v] = min(reach[v],reach[w]);
		}
		return reach[v];
	}
};