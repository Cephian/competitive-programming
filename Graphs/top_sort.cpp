struct top_sort {
	vector<vector<int>> G; //stores G; take it out if you want to use it elsewhere
	vector<int> order; //stores the topological sort
	vector<short> seen;
	void init(int n) { G.resize(n); seen.resize(n); }
	top_sort(int n) { init(n); }
	
	//add a new edge
	inline void add_edge(int u, int v) { G[u].push_back(v); }

	bool visit(int u) {
		if(seen[u] == 2) return true;
		if(seen[u] == 1) return false;
		seen[u] = 1;
		for(int v : G[u])
			if(!visit(v))
				return false;
		seen[u] = 2;
		order.push_back(u);
		return true;
	}
	//topologically sort
	bool sort() {
		for(int i = 0; i < G.size(); ++i)
			if(!visit(i))
				return false;
		reverse(order.begin(),order.end());
		return true;
	}
};
