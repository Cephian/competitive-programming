//pass in 0-indexed array A of length n to constructor
template <class T>
struct elem_freq {
	unordered_map<T,vector<int> > idx;
	vector<T> v;
	void build(T* A, int n) {
		v = vector<T>(n,0);
		idx.clear();
		for(int i = 0; i < n; ++i) {
			v[i] = A[i];
			idx[A[i]].push_back(i);
		}
	}

	// finds the number of x's in [l,r] in O(log n)
	inline int in_range(T x, int l, int r) const {
		if(r-l < 50) {
			int a=0;
			for(int i = l; i <= r; ++i)
				a+= v[i]==x;
			return a;
		}
		if(!idx.count(x)) return 0;
		const vector<int> &v = idx[x];
		if(v.back() < l || v[0] > r) return 0;
		int i=-1, k=v.size(),j=k-1;
		while(j-i>1) {
			int m = (i+j)/2;
			(v[m]<l?i:j)=m;
		}
		if(v[i=j]>r) return 0;
		while(k-i>1) {
			int m = (i+k)/2;
			(v[m]>r?k:i)=m;
		}
		return max(0,i-j+1);
	}
};