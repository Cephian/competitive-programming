#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

//answers range queries with inequalities in O(log^2 n)
//can be modified to compute other decomposable values of a list
//e.g. xor in [l,r] of elements <= k
template <class T>
struct range_leq {
	int N;
	vector<vector<T> > fen;
	range_leq(int *A, int n):N(n+1),fen(N) {
		for(int i = 1; i < N; ++i) {
			int p = 1;
			for(;!(p&i);p<<=1);
			for(;p;--p)
				fen[i].push_back(A[i-p]);
			sort(fen[i].begin(),fen[i].end());
		}
	}

	// how many elements in [0,i] have value in (-INF,v] ?
	inline int prefix_query(int i, T v) const {
		int ans = 0;
		for(++i;i;i^=i&-i) {
			int lo=-1,hi=fen[i].size();
			while(hi-lo!=1) {
				int md = (lo+hi)/2;
				(fen[i][md]<=v?lo:hi)=md;
			}
			ans += hi;
		}
		return ans;
	}

	// how many elements in [l,r] have value in (-INF,v] ?
	inline int range_query(int l, int r, int v) {
		return prefix_query(r,v) - prefix_query(l-1,v);
	}

	// how many elements in [l,r] have value in [w,v] ?
	inline int box_query(int l, int r, int w, int v) {
		return range_query(l,r,v) - range_query(l,r,w-1);
	}
};