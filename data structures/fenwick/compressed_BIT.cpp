//compressed fenwick tree, 0-indexed
template <class T>
struct cmp_bit {
	int N;
	unordered_map<int,T> b{{0,0}};

	void init(int n){N=n+1;}
	cmp_bit(){}
	cmp_bit(int n){init(n);}

	inline void update(int i, T v) {
		for(++i;i < N; i += i&-i)
			b[i] += v;
	}

	//sum of the first i values
	inline T prefix(int i) {
		int a = 0;
		for(;i;i ^= i&-i)
			a += b[i];
		return a;
	}

	inline T query(int l, int r) {
		return prefix(r+1)-prefix(l);
	}
};