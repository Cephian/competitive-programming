//point update, range query, 0-indexed
template <class T>
struct bit {
	vector<T> b;
	void init(int n){b.resize(n+1);}
	bit(){}
	bit(int n){init(n);}
	inline void update(int i, T v) {
		for(++i; i<b.size(); i+=i&-i)
			b[i] += v;
	}
	//sum of the first i values
	int prefix(int i) const {
		T a = 0;
		for(; i; i^=i&-i)
			a += b[i];
		return a;
	}
	inline int query(int l, int r) const {
		return prefix(r+1)-prefix(l);
	}
};