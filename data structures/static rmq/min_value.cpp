// O(n log n) space, O(1) query RMQ
struct rmq {
	vector<vector<int> > t;
	rmq(){}
	rmq(int* a, int n):t(32-__builtin_clz(n),vector<int>(n)) {
		for(int i = 0; i < n; ++i)
			t[0][i] = a[i];
		for(int k = 1, p = 1; k < t.size(); ++k, p<<=1)
			for(int i = 0; i < n; ++i)
				t[k][i] = (i+p<n)?min(t[k-1][i],t[k-1][i+p]):t[k-1][i];
	}
	//inclusive min query
	inline int query(int l, int r) const {
		int p = 31-__builtin_clz(r-l+1);
		return min(t[p][l],t[p][r+1-(1<<p)]);
	}
};