template <class T>
struct wavelet{

	struct node {
		vector<int> b;
		int lo,hi,md;
	};
	vector<node> t;

	void build(const vector<T> &c, T *A, T *B, int v, int i, int j) {
		t[v].b.resize(B-A+1);
		t[v].lo = c[i], t[v].hi = c[j], t[v].md = c[(i+j)/2];
		for(int i = 0; A+i != B; ++i)
			t[v].b[i+1] = t[v].b[i] + (A[i]<=t[v].md);
		if(i == j) return;
		T *p = stable_partition(A,B,[=](int x){return x <= t[v].md;});
		build(c,A,p,v<<1,i,(i+j)/2);
		build(c,p,B,v<<1|1,(i+j)/2+1,j);
	}

	void init(T *A, int n) {
		vector<T> c(A,A+n);
		sort(c.begin(),c.end());
		c.erase(unique(c.begin(),c.end()),c.end());
		int N = c.size();
		t.resize(N<<2);
		build(c,A,A+n,1,0,N-1);
	}

	wavelet(){}
	wavelet(T *A, int n){init(A,n);}

	//kth smallest element in [l, r]
	T kth(int l, int r, int k, int v = 1) {
		if(t[v].lo == t[v].hi) return t[v].lo;
		int lb = t[v].b[l], rb = t[v].b[r+1], il = rb-lb;
		return (k < il) ? kth(lb,rb-1,k,v<<1) : kth(l-lb,r-rb,k-il,v<<1|1);
	}

	//number of elements in [l,r] <= to a
	int leq(int l, int r, T a, int v = 1) {
		if(a < t[v].lo) return 0;
		if(t[v].hi <= a) return r-l+1;
		int lb = t[v].b[l], rb = t[v].b[r+1];
		return leq(lb,rb-1,a,v<<1) + leq(l-lb,r-rb,a,v<<1|1);
	}

	//number of elements in [l, r] equal to a
	int count(int l, int r, T a, int v = 1) {
		if(a < t[v].lo || a > t[v].hi) return 0;
		if(t[v].lo == t[v].hi) return r-l+1;
		int lb = t[v].b[l-1], rb = t[v].b[r];
		if(a <= t[v].md) return count(lb,rb-1,a,v<<1);
		return count(l-lb,r-rb,a,v<<1|1);
	}
};