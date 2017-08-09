//point SET update, range MIN query
template <class T>
struct segt {
	int N;
	vector<T> t;
	segt(int N):N(N),t(2*N){}

	constexpr static T NONE = numeric_limits<T>::highest();
	static inline T combine(T a, T b) {return min(a,b);}

	//update point i
	void update(int i, T val) {
		for(t[i+=N] = val;i>1;i>>=1)
			t[i>>1] = combine(t[i],t[i^1]);
	}

	//query range [l,r]
	T query(int l, int r) const {
		T ans = NONE;
		for(l+=N,r+=N+1;l<r;l>>=1,r>>=1) {
			if(l&1) ans = combine(ans,t[l++]);
			if(r&1) ans = combine(ans,t[--r]);
		}
		return ans;
	}
};