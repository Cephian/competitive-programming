vvi T;

const int N = 1e5+5;
int cdt_sz[N]={};
int cdt_parent[N];
vi cdt_children[N];

int cdt_fsz(int u, int v) {
	if(cdt_sz[v] == -1) return 0;
	cdt_sz[v] = 1;
	for(int w : T[v])
		if(w != u)
			cdt_sz[v] += cdt_fsz(v,w);
	return cdt_sz[v];
}

//call cdt_build(0, tree_size)
//cdt_parent of the centroid root is -1
int cdt_build(int v, int n, bool rc = 1) {
	if(rc) cdt_fsz(-1,v);
	int p = -1;
	while(1) {
		int x = -1;
		for(int w : T[v])
			if(x == -1 || cdt_sz[w] > cdt_sz[x])
				x = w;
		if(cdt_sz[x] * 2 <= n) break;
		cdt_sz[v] = n-cdt_sz[x];
		p = v, v = x;
	}
	cdt_sz[v] = cdt_parent[v] = -1;
	for(int w : T[v]) {
		if(cdt_sz[w] == -1) continue;
		int x = cdt_build(w,cdt_sz[w],w == p);
		//found cdt edge (v -> x)
		cdt_children[v].push_back(x);
		cdt_parent[x] = v;
	}
	return v;
}