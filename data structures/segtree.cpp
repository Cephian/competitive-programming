#include <bits/stdc++.h>

//point SET update, range MIN query
template <class T>
struct segt {
	int N;
	vector<T> t;
	segt(int N):N(N),t(2*N){}

	const static T NONE = 1<<30;
	inline T combine(T a, T b) {return min(a,b);}

	//update point i
	void update(int i, T val) {
		for(t[i+=N] = val;i>1;i>>=1)
			t[i>>1] = combine(t[i],t[i^1]);
	}

	//query range [l,r)
	T query(int l, int r) {
		T ans = NONE;
		for(l+=N,r+=N;l<r;l>>=1,r>>=1) {
			if(l&1) ans = combine(ans,t[l++]);
			if(r&1) ans = combine(ans,t[--r]);
		}
		return ans;
	}
};

//range ADD update, point SUM query
template <class T>
struct segt {
	int N;
	vector<T> t;
	segt(int N):N(N),t(2*N){}

	const static T NONE = 0;

	//add val to [l,r)
	void update(int l, int r, T val) {
		for(l+=N,r+=N;l<r;l>>=1,r>>=1) {
			if(l&1) t[l++] += val;
			if(r&1) t[--r] += val;
		}
	}

	//query range [l,r)
	T query(int i) {
		T ans = NONE;
		for(i+=n;i;i>>=1) ans += t[i];
		return ans;
	}
};

int main() {
	int n,q,i,j;
	scanf("%d",&n);
	segt<int> T(n);
	for(int i = 0; i < n; ++i) {
		// scanf("%d",&j);
		// T.update(i,j);
		scanf("%d",&T.t[i+n]);
	}
	for(int i = n-1; i; --i)
		T.t[i] = T.combine(T.t[i<<1],T.t[i<<1|1]);
	scanf("%d",&q);
	while(q--) {
		scanf("%d%d",&i,&j);
		printf("%d\n",T.query(i,j+1));
	}
	return 0;
}