const int N = 100005;
ll segt[4*N],lazy[4*N];
int l[4*N],r[4*N];

void build_st(int v, int i, int j) {
	l[v] = i;
	r[v] = j;
	//CHANGE ME
	segt[v] = lazy[v] = 0;
	if(i == j) return;
	build_st(v*2,i,(i+j)/2);
	build_st(v*2+1,(i+j)/2+1,j);
}

ll get_val(int v) {
	//CHANGE ME
	return segt[v]+lazy[v];
}

void prop(int v) {
	//CHANGE ME
	lazy[v*2]+=lazy[v];
	lazy[v*2+1]+=lazy[v];
	lazy[v]=0;
}

void recalc(int v) {
	//CHANGE ME
	segt[v] = max(get_val(v*2),get_val(v*2+1));
}

void update_st(int v, int i, int j, ll val) {
	if(j < l[v] || r[v] < i) return;
	if(i <= l[v] && r[v] <= j) {
		//CHANGE ME
		lazy[v] += val;
		return;
	}
	prop(v);
	update_st(v*2,i,j,val);
	update_st(v*2+1,i,j,val);
	recalc(v);
}

ll query_st(int v, int i, int j) {
	if(j < l[v] || r[v] < i) {
		//CHANGE ME
		return 0;
	}
	if(i <= l[v] && r[v] <= j) {
		//CHANGE ME
		return get_val(v);
	}
	prop(v);
	recalc(v);
	//CHANGE ME
	return max(query_st(v*2,i,j),query_st(v*2+1,i,j));
}
