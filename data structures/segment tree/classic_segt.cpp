struct segt {
	int N = 100005;
	vector<ll> t,lazy;
	vector<int> l,r;

	void build(int i, int j, int v) {
		l[v] = i, r[v] = j;
		//CHANGE ME
		t[v] = lazy[v] = 0;
		if(i == j) return;
		build(i,(i+j)/2,v<<1);
		build((i+j)/2+1,j,v<<1|1);
	}

	void init(int n) {
		N = n;
		t.resize(4*n), lazy.resize(4*n);
		l.resize(4*n), r.resize(4*n);
		build(0,n-1,1);
	}

	segt(){}
	segt(int n){init(n);}

	// --- CHANGE ME ---
	inline ll merge(ll a, ll b) {
		return max(a,b);
	}

	// --- CHANGE ME ---
	//propagate lazy value downwards
	inline void prop(int v) {
		if(l[v]!=r[v]) {
			lazy[v<<1] += lazy[v];
			lazy[v<<1|1] += lazy[v];
		}
		t[v] += lazy[v];
		lazy[v] = 0;
	}

	void update(int i, int j, ll val, int v = 1) {
		if(j < l[v] || r[v] < i) return;
		if(i <= l[v] && r[v] <= j) {
			// --- CHANGE ME ---
			//apply lazy update to v's range
			lazy[v] += val;
			return;
		}
		prop(v);
		update(i,j,val,v<<1);
		update(i,j,val,v<<1|1);
		prop(v<<1), prop(v<<1|1);
		t[v] = merge(t[v<<1],t[v<<1|1]);
	}

	ll query(int i, int j, int v = 1) {
		if(j < l[v] || r[v] < i) {
			// --- CHANGE ME ---
			//return result for empty range
			return 0;
		}
		prop(v);
		if(i <= l[v] && r[v] <= j)
			return t[v];
		return merge(query(i,j,v<<1),query(i,j,v<<1|1));
	}
};