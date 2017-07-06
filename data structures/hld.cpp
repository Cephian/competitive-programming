vvi T;

// heavy-light decomposition for general range query structures
// for edge update (u,v), simply update MAX(hld_ind[u],hld_ind[v])
int hld_sz[N], hld_ind[N], hld_parent[N], hld_cstart[N], hld_pr[N], hld_ctr;

int hld_fsz(int v, int u = -1) {
	hld_sz[v] = 1;
	for(int w : T[v])
		if(w != u)
			hld_sz[v] += hld_fsz(w,v);
	return hld_sz[v];
}

void hld(int v = 0, int u = -1, int head = 0, int d = 0) {
	if(u == -1) hld_ctr=0,hld_fsz(v);
	else hld_parent[hld_ctr] = hld_ind[u];
	hld_cstart[hld_ctr] = head;
	hld_pr[hld_ctr] = d;
	hld_ind[v] = hld_ctr++;
	int lg = -1;
	for(int w : T[v])
		if(w != u && (lg == -1 || hld_sz[w] > hld_sz[lg]))
			lg = w;
	if(lg != -1) hld(lg,v,head,d);
	for(int w : T[v]) {
		if(w == u || w == lg) continue;
		hld(w,v,hld_ctr,d+1);
	}
}

//remember to make queries inclusive
void path_query(int u, int v) {
	u = hld_ind[u], v = hld_ind[v];
	while(hld_cstart[u] != hld_cstart[v]) {
		if(hld_pr[u] < hld_pr[v]) swap(u,v);
		// combine : QUERY [hld_cstart[u], u]
		u = hld_parent[hld_cstart[u]];
	}
	if(u > v) swap(u,v);
	//combine (vert query): QUERY [u,v]
	//combine (edge query): QUERY [u+1,v]
	return mx;
}