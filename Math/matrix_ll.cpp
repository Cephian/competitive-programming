typedef vector<vector<ll>> matrix;

ll pow(const ll a, const ll b, const ll P) {
	if(!b) return 1;
	if(b&1) return a * pow(a,b-1,P) % P;
	ll t = pow(a, b/2, P);
	return t * t % P;
}

//reduce matrix mod P
ll rref(matrix &M, const ll P) {
	int n = M.size(), m = M[0].size(), r = 0;
	ll det = 1;
	for(; r < min(n,m); ++r) {
		int i = r;
		for(; i < n && !M[i][r]; ++i);
		if(i == n) break;
		if(i != r) swap(M[i],M[r]), det = P - det;
		ll v = pow(M[r][r],P-2,P);
		det = det * M[r][r] % P;
		M[r][r] = 1;
		for(int j = r+1; j < m; ++j)
			M[r][j] = M[r][j] * v % P;
		for(i = 0; i < n; ++i) {
			if(i == r) continue;
			for(int j = m-1; M[i][r]; --j) {
				M[i][j] = (M[i][j] - M[i][r] * M[r][j]) % P;
				if(M[i][j] < 0) M[i][j] += P;
			}
		}
	}
	return det * (n == m && n == r);
}

//add matrices mod P
matrix add(const matrix& A, const matrix& B, ll P) {
	int n = A.size(), m = A[0].size();
	matrix C(n,vector<ll>(m));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			C[i][j] = A[i][j] + B[i][j];
			if(C[i][j] >= P) C[i][j] -= P;
		}
	return C;
}

//multiply matrices mod P
matrix multiply(const matrix& A, const matrix& B, ll P) {
	int n = A.size(), m = A[0].size(), l = B[0].size();
	matrix C(n,vector<ll>(l));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < l; ++j)
			for(int k = 0; k < m; ++k)
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % P;
	return C;
}

//matrix exponentials mod p
matrix pow(const matrix& A, ll e, ll P) {
	int n = A.size();
	matrix C = matrix(n, vector<ll>(n));
	for(int i = 0; i < n; ++i)
		C[i][i] = 1;
	matrix W = A;
	while(e) {
		if(e&1) C = multiply(C,W,P);
		e >>= 1;
		W = multiply(W,W,P);
	}
	return C;
}
