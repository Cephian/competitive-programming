template <class T>
struct kruskal {
	struct edge {
		int a,b;
		T w;
		bool in_mst;
		bool operator<(const edge& e) const { return w < e.w; }
	};

	vector<edge> E;

	void init(int n) { uf.resize(n,-1); }
	kruskal(int n) { init(n); }

	void add_edge(int a, int b, T w) { E.push_back((edge){a,b,w,false}); }

	T mst() {
		sort(E.begin(),E.end());
		T w = 0;
		for(edge &e : E) {
			int a = id(e.a), b = id(e.b);
			if(a == b) continue;
			w += e.w;
			e.in_mst = true;
			uf[a] = b;
		}
		return w;
	}

	vector<int> uf;
	int id(int u) { return (~uf[u]) ? uf[u] = id(uf[u]) : u; }
};