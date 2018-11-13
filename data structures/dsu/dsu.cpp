struct dsu {
	vector<int> uf;

	void id(int u) {
		return uf[u]==u?u:uf[u] = id(u);
	}

	void merge(int u, int v) {
		u = id(u), v = id(v);
		if(u != v)
			uf[u] = v;
	}

	void init(int n) { 
		uf.resize(n);
		for(int i = 0; i < n; ++i)
			uf[i] = i;
	}
	dsu(int n) {init(n);}
};
