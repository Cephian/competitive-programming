// construct graph G and call fill_scc
// sz is the # of SCCs and scc[v] in {0,...,sz-1} is the SCC of v
// sz-1,sz-2,...,1,0 is a topological ordering of the SCCs

const int N = 1e5+5;

//set ls = sz = scc[v] = 0 between runs
vvi G, R;
int L[N], ls=0, scc[N]={0}, sz=0;
void dfs1(int v) {
	if(scc[v]) return;
	scc[v] = 1;
	for(auto u : G[v])
		dfs1(u);
	L[ls++] = v;
}

void dfs2(int v, int r) {
	if(scc[v] != -1) return;
	scc[v] = r;
	for(auto u : R[v])
		dfs2(u,r);
}

void fill_scc() {
	int n = G.size();
	R = vvi(n,vi());
	for(int v = 0; v < n; ++v) {
		dfs1(v);
		for(int u : G[v])
			R[u].push_back(v);
	}
	fill(scc,scc+n,-1);
	for(int i = n-1; i >= 0; --i) {
		if(scc[L[i]] == -1)
			dfs2(L[i],sz++);
	}
}

//only implement if you need the digraph of SCCs
//reverse index order |B|-1,|B|-2,...,2,1,0 is a topological ordering
void scc_digraph(vvi& B) {
	B = vvi(sz,vi());
	for(int v = 0; v < G.size(); ++v) {
		for(int u : G[v])
			if(scc[v] != scc[u])
				B[v].push_back(u);
		sort(B[v].begin(),B[v].end());
		B[v].erase(unique(B[v].begin(),B[v].end()),B[v].end());
	}
}
