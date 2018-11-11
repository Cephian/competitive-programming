//initialize me
int L,R;
ll dp[K][N], A, INF = 1<<62;

//remove array[i] from the range
inline void sl_rem(int i) {
	// A -= a[i];
}

//add array[i] to the range
inline void sl_add(int i) {
	// A += a[i];
}

inline ll slide(int l, int r) {
	while(l < L) sl_add(--L);
	while(R < r) sl_add(++R);
	while(L < l) sl_rem(L++);
	while(r < R) sl_rem(R--);
	//return A
}

// dp[k][i] = MAX{j <= i} dp[k-1][j-1] + cost(j .. i)
// ONE INDEX YOUR ARRAY, AND SET dp[?][0] = 0
void compute(int k, int l, int r, int bl, int br) {
	int m = (l+r)/2, opt;
	dp[k][m] = INF;
	for(int i = bl; i <= min(br,m); ++i) {
		slide(i,m);
		ll cost = A + dp[k-1][i-1];
		if(cost < dp[k][m])
			dp[k][m] = cost, opt = i;
	}
	if(l <= m-1) compute(k,l,m-1,bl,opt);
	if(m+1 <= r) compute(k,m+1,r,opt,br);
}
