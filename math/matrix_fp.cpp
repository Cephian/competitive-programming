typedef vector<vector<double> > matrix;
constexpr double EPS = 1e-10;

double rref(matrix &M) {
	int n = M.size(), m = M[0].size(), r = 0;
	double det = 1;
	for(; r < min(n,m); ++r) {
		int i = r;
		for(; i < n && abs(M[i][r]) < EPS; ++i);
		if(i == n) break;
		if(i != r) swap(M[i],M[r]), det = -det;
		double v = 1.0/M[r][r];
		det = det * M[r][r];
		M[r][r] = 1;
		for(int j = r+1; j < m; ++j)
			M[r][j] = M[r][j] * v;
		for(i = 0; i < n; ++i) {
			if(i == r) continue;
			for(int j = m-1; j >= r; --j)
				M[i][j] = M[i][j] - M[i][r] * M[r][j];
		}
	}
	return det * (n == m && n == r);
}