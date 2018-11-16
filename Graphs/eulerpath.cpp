#include <bits/stdc++.h>
using namespace std;

//note: destroys the graph in the process
// and returns path/circuit backwards

// ----- DIGRAPH -----
void dg_euler(int v, vector<int>& path, vector<vector<int>>& G) {
	while(G[v].size()) {
		int u = G[v].back();
		G[v].pop_back();
		dg_euler(u,path,G);
	}
	path.push_back(v);
}

// ----- UNDIRECTED GRAPH -----
struct euler_path {
	vector<int> e1,e2;
	vector<vector<int>> G;
	vector<bool> used = {};

	void init(int N){G.resize(N);}

	inline void add_edge(int u, int v) {
		G[u].push_back(e1.size()), G[v].push_back(e2.size());
		e1.push_back(u), e2.push_back(v);
		used.push_back(0);
	}

	void get_path(vector<int> &path, int v = 0) {
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

	euler_path(int N){init(N);}
};


// ----- USAGE -----
vector<vector<int>> G;
int main() {
	euler_path e(10);
	// add edges
	vector<int> path;
	e.get_path(path);

	//DIRECTED CASE
	G = {{2,3},{0},{1},{4},{0}};
	path.resize(0);
	dg_euler(1,path,G);
	for(auto u : path)
		cout << u << "\n";
	cout << endl;
}