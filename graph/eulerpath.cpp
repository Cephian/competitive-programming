//note: destroys the graph in the process
// and returns path/circuit backwards

// ----- DIGRAPH -----
void dg_euler(int v, vi& path, vvi& G) {
	while(G[v].size()) {
		int u = G[v].back();
		G[v].pop_back();
		dg_euler(u,path,G);
	}
	path.push_back(v);
}

// ----- UNDIRECTED GRAPH -----
struct euler_path {
	vi e1,e2;
	vvi G;
	vector<bool> used = {};

	euler_path(){}
	euler_path(int N):G(N){}
	euler_path(int N, int M):G(N){used.reserve(M);}

	void get_path(vi& path, int v = 0) {
		while(G[v].size()) {
			int i = G[v].back();
			G[v].pop_back();
			if(used[i]) continue;
			used[i] = 1;
			int u = (v==e1[i])?e2[i]:e1[i];
			get_path(path,u);
		}
		path.push_back(v);
	}

	inline void add_edge(int u, int v) {
		G[u].push_back(e1.size()), G[v].push_back(e2.size());
		e1.push_back(u), e2.push_back(v);
		used.push_back(0);
	}
};


// ----- USAGE -----
vvi G;
int main() {
	euler_path e(10);
	// add edges
	vi path;
	e.get_path(path);

	//DIRECTED CASE
	G = {{2,3},{0},{1},{4},{0}};
	path = vi();
	dg_euler(1,path,G);
	for(auto u : path)
		cout << u << "\n";
	cout << endl;
}