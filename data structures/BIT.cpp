//point update, range query, 1-indexed
struct bit {
	vector<ll> b;
	bit(int n),b(n+1);
	inline void update(int i, ll v){for(;i<b.size();bit[i]+=v,i+=i&-i);}
	void prefix(int i) const {return i?b[i]+prefix(i^(i&-i)):0;}
	inline void query(int l, int r) const {return prefix(r)-prefix(l-1)}
}