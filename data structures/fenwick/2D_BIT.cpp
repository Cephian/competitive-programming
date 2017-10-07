//2d fenwick tree, 1-indexed
template <class T>
struct bit_2d {
	int N,M;
	vector<vector<T>> b;

	void init(int n, int m){N=n+1,M=m+1,b=vector<vector<T>>(N,vector<T>(M));}
	bit_2d(){}
	bit_2d(int n, int m){init(n,m);}

	inline void update(int i, int j, T v) {
		for(;i < N; i += i&-i)
			for(int k = j; k < M; k += k&-k)
				b[i][k] += v;
	}

	//xor of the 'prefix' i x j rectangle
	inline T prefix(int i, int j) {
		T a = 0;
		for(;i;i ^= i&-i)
			for(int k = j;k;k ^= k&-k)
				a += b[i][k];
		return a;
	}

	inline T query(int a, int b, int c, int d) {
		return prefix(c,d)+prefix(a-1,b-1)-prefix(a-1,d)-prefix(c,b-1);
	}
};