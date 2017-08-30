//FIND longest increasing subsequence
int lis(int *A, int n) {
	if(!n) return 0;
	vector<int> v = {0};
	for(int i = 1; i < n; ++i) {
		if(A[i] > A[v.back()]) {
			v.push_back(i);
		} else {
			int lo = -1, hi = v.size()-1;
			while(hi-lo>1) {
				int md = (lo+hi)/2;
				((A[i] > A[v[md]])?lo:hi) = md;
			}
			v[hi] = i;
		}
	}
	return v.size();
}



//CONSTRUCT longest increasing subsequence
//store results in L (assumed to be empty)
int lis(int *A, int n, vector<int> &L) {
	if(!n) return 0;
	vector<int> v = {n-1}, p = {-1};
	for(int i = n-2; i >= 0; --i) {
		if(A[i] < A[v.back()])
			p[i] = v.back(), v.push_back(i);
		else {
			int lo = -1, hi = v.size()-1;
			while(hi-lo>1) {
				int md = (lo+hi)/2;
				((A[i] < A[v[md]])?lo:hi) = md;
			}
			p[i] = (lo == -1)?-1:v[lo];
			v[hi] = i;
		}
	}
	L.reserve(v.size());
	for(int u = v.back(); ~u; u = p[u])
		L.push_back(u);	
	return L.size();
}