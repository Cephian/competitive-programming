#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//range ADD update, range MIN query
template <class T>
struct segt {
	int N,h;
	vector<T> t,d;
	segt();
	segt(int N):N(N),t(2*N),d(N){h = 32 - __builtin_clz(N);}

	const static T NONE = numeric_limits<T>::max(); //min()
	inline static T combine(const T a, const T b) {return min(a,b);}

	inline void apply(int p, T value) {
		t[p] += value;
		if(p < N) d[p] += value;
	}

	inline void build(int p) {
		while(p > 1) p >>= 1, t[p] = combine(t[p<<1], t[p<<1|1]) + d[p];
	}

	inline void push(int p) {
		for(int i,s = h; s > 0; --s) {
			if(d[i = p >> s]) {
				apply(i<<1, d[i]);
				apply(i<<1|1, d[i]);
				d[i] = 0;
			}
		}
	}

	//[l,r] range update
	inline void update(int l, int r, T value) {
		int l0 = (l += N), r0 = (r += N+1)-1;
		for(; l < r; l >>= 1, r >>= 1) {
			if(l&1) apply(l++, value);
			if(r&1) apply(--r, value);
		}
		build(l0), build(r0);
	}

	// [l,r] range query
	inline T query(int l, int r) {
		push(l += N);
		push((r += N+1) - 1);
		T res = NONE;
		for (; l < r; l >>= 1, r >>= 1) {
			if(l&1) res = combine(res, t[l++]);
			if(r&1) res = combine(t[--r], res);
		}
		return res;
	}
};