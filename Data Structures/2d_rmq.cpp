// 2d min range query in O(n*m*log(n)*nlog(m) space, O(1) query
template <class T>
struct rmq_2d {
	vector<vector<vector<vector<T>>>> t;
	rmq_2d(){}
	void init(const int n, const int m) {
		const int logn = 32-__builtin_clz(n);
		const int logm = 32-__builtin_clz(m);
		t.resize(logn, vector<vector<vector<T>>>(logm, vector<vector<T>>(n, vector<T>(m))));
	}
	rmq_2d(int n, int m){init(n, m);}
 
	vector<T>& operator [](int i) {
		return t[0][0][i];
	}
 
	// change me for max query
	inline T combine(T a, T b) {
		return min(a, b);
	}
 
	void build() {
		const int logn = t.size();
		const int logm = t[0].size();
		const int n = t[0][0].size();
		const int m = t[0][0][0].size();
		for(int i = 0; i < logn; ++i) {
			for(int j = 0; j < logm; ++j) {
				if(i == 0 && j == 0) continue;
				for(int k = 0; k < n; ++k) {
					for(int l = 0; l < m; ++l) {
						if(j == 0)
							t[i][j][k][l] = combine(t[i-1][j][k][l], t[i-1][j][min(n-1, k+(1<<(i-1)))][l]);
						else
							t[i][j][k][l] = combine(t[i][j-1][k][l], t[i][j-1][k][min(m-1, l+(1<<(j-1)))]);
					}
				}
			}
		}
	}
 
	// inclusive min query
	T query(int a, int b, int c, int d) {
		const int i = 31-__builtin_clz(c-a+1);
		const int j = 31-__builtin_clz(d-b+1);
		const int dx = (1<<i)-1;
		const int dy = (1<<j)-1;
		T ans  = t[i][j][a][b];
		ans = combine(ans, t[i][j][c-dx][b]);
		ans = combine(ans, t[i][j][a][d-dy]);
		ans = combine(ans, t[i][j][c-dx][d-dy]);
		return ans;
	}
};

void main() {
	//init
	rmq_2d R(n, m);
	//populate
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			cin >> R[i][j];
	// build
	R.build();
	// query
	cout << query(1,2,5,6) << endl;
}
