//range SET update, point VALUE query
template <class T>
struct segt {
	int N,ctr=1;
	vector<T> t,v;
	
	segt(int N):N(N),t(2*N),v(2*N){}
	//set range [l,r]
	inline void update(int l, int r, T c) {
		for(l+=N,r+=N+1;l<r;l>>=1,r>>=1) {
			if(l&1) t[l]=ctr,v[l++]=c;
			if(r&1) t[--r]=ctr,v[r]=c;
		}
		++ctr;
	}

	//query value at i
	inline int query(int i) const {
		T lv = -1;
		int lt = -1;
		for(i += N; i > 0; i >>= 1)
			if(t[i]>lt) lt=t[i],lv=v[i];
		return lv;
	}
};
