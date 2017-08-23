//range XOR update, point VAL query
struct segt {
	int N;
	vector<bool> t;
	segt(){}
	segt(int N):N(N),t(2*N){}

	//xor [l,r]
	inline void flip(int l, int r) {
		for(l+=N,r+=N+1;l<r;l>>=1,r>>=1) {
			if(l&1) t[l] = !t[l], l++;
			if(r&1) --r, t[r] = !t[r];
		}
	}

	//query point i
	inline bool get(int i) const {
		bool ans = 0;
		for(i+=N;i;i>>=1) ans ^= t[i];
		return ans;
	}
};