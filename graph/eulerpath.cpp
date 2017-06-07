//note: destroys the graph in the process
// and returns path/circuit backwards

// ----- DIGRAPH -----
void dg_euler(int v, vi& path, vvi& G) {
	if(G[v].size()) {
		int u = G[v].back();
		G[v].pop_back();
		dg_euler(u,path,G);
	}
	path.push_back(v);
}

// ----- UNDIRECTED GRAPH -----
vi e1,e2;
//remember to clear between runs
bool used[100005] = {0};

void ud_euler(int v, vi& path, vvi& G) {
	int i = -1;
	do {
		i = G[v].back();
		G[v].pop_back();
	}
	while(G[v].size() && used[i]);
	if(i != -1 && !used[i]) {
		used[i]=1;
		int u = (v==e1[i])?e2[i]:e1[i];
		ud_euler(u,path,G);
	}
	path.push_back(v);
}

// ----- USAGE -----
vvi G;
int main() {
	//UNDIRECTED CASE
	//EDGES FROM e1[i] <-> e2[i] 
	//G STORES INDICES OF EDGES IN ADJ LIST
	e1 = {0,2,1,2,0,4,4,4,4,5,5};
	e2 = {1,0,3,1,3,0,1,2,3,2,3};
	G = vvi(6,vi());
	for(int i = 0; i < e1.size(); ++i) {
		G[e1[i]].push_back(i);
		G[e2[i]].push_back(i);
	}

	vi path;
	ud_euler(0,path,G);
	for(auto u : path)
		cout << u << " ";
	cout << endl;

	//DIRECTED CASE
	G = {{2,3},{0},{1},{4},{0}};
	path = vi();
	dg_euler(1,path,G);
	for(auto u : path)
		cout << u << "\n";
	cout << endl;
}