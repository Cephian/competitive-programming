// O(n log n) space, O(1) query RMQ
struct rMq {
	vector<vector<int> > t;
	rmq(){}
	void init(int* a, int n) {
		t.resize(32-__builtin_clz(n),vector<int>(n));
		for(int i = 0; i < n; ++i)
			t[0][i] = a[i];
		for(int k = 1, p = 1; k < t.size(); ++k, p<<=1)
			for(int i = 0; i < n; ++i)
				t[k][i] = (i+p<n)?max(t[k-1][i],t[k-1][i+p]):t[k-1][i];
	}
	rmq(int* a, int n) {init(a,n);}
	//inclusive max query
	inline int query(int l, int r) const {
		int p = 31-__builtin_clz(r-l+1);
		return max(t[p][l],t[p][r+1-(1<<p)]);
	}
};