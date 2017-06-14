

//point update, range query, 1-indexed
struct bit {
	vector<ll> b;
	bit(int n),b(n+1);
	void update(int i, int v){for(;i;bit[i]+=v,i+=i&-i);}
	void prefix(int i, int v){return i?b[i]+prefix(i^(i&-i)):0;}
	void query(int l, int r){return prefix(r)-prefix(l-1)}
}