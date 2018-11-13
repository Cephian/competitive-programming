//2d compressed fenwick tree, 0-indexed
template <class T>
struct cmp_2d_bit {
	int N,M;
	vector<unordered_map<int,T>> b;

	void init(int n, int m) {N=n+1,M=m+1;b.resize(N,{{0,0}});}
	cmp_2d_bit() {}
	cmp_2d_bit(int n, int m) {init(n,m);}

	inline void update(int x, int y, T v) {
		for(++x; x<N; x+=x&-x)
			for(int z = y+1; z<M; z+=z&-z)
				b[x][z] += v;
	}

	inline T prefix(int x, int y) {
		T a = 0;
		for(++x; x; x^=x&-x)
			for(int z = y+1; z; z^=z&-z)
				a += b[x][z];
		return a;
	}

	inline T query(int x1, int y1, int x2, int y2) {
		return prefix(x2,y2) - prefix(x1-1,y2) - prefix(x2,y1-1) + prefix(x1-1,y1-1);
	}
};
