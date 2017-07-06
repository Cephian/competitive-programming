//range ADD update, point VAL query
template <class T>
struct segt {
	int N;
	vector<T> t;
	segt(int N):N(N),t(2*N){}

	constexpr static T NONE = 0;

	//add val to [l,r)
	inline void update(int l, int r, T val) {
		for(l+=N,r+=N;l<r;l>>=1,r>>=1) {
			if(l&1) t[l++] += val;
			if(r&1) t[--r] += val;
		}
	}

	//query range [l,r)
	inline T query(int i) const {
		T ans = NONE;
		for(i+=n;i;i>>=1) ans += t[i];
		return ans;
	}
};