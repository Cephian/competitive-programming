//range update, point query, 0-indexed
template <class T>
struct bit {
	vector<T> b;
	void init(int n){b.resize(n+1);}
	bit(){}
	bit(int n){init(n);}
	inline void ud(int i, T v) {
		for(; i<b.size(); i+=i&-i)
			b[i] += v;
	}
	//update [l,r] with value v
	inline void update(int l, int r, T v) {
		ud(l+1,v);
		if(r+2<b.size())ud(r+2,-v);
	}

	//get value at i
	inline int query(int i) const {
		T a = 0;
		for(++i; i; i^=i&-i)
			a += b[i];
		return a;
	}
};