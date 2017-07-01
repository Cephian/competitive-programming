#include <bits/stdc++.h>
using namespace std;

int nm=0;

struct node {
	vector<int> b;
	int lo,hi,md;
};

template <class T>
struct wavelet{
	vector<T> c;
	vector<node> t;
	 
	int leq_cmp(T x) {
		int lo = 0, hi = c.size(),md;
		while(hi-lo!=1) md = (lo+hi)>>1,((c[md]<=x)?lo:hi) = md;
		return lo;
	}

	void build(T *A, T *B, int v) {
		t[v].b.resize(B-A+1);
		for(int i = 0; A+i != B; ++i)
			t[v].b[i+1] = t[v].b[i] + (A[i]<=c[t[v].md]);
		if(t[v].lo==t[v].hi) return;
		T *p = stable_partition(A,B,[=](int x){return x <= c[t[v].md];});
		build(A,p,v<<1);
		build(p,B,v<<1|1);
	}

	wavelet(T *A, int n) {
		c.resize(n+1);
		c[0] = numeric_limits<T>::lowest();
		copy(A,A+n,&c[1]);
		sort(c.begin(),c.end());
		c.erase(unique(c.begin(),c.end()),c.end());
		int N = c.size();
		t = vector<node>(N<<1);
		for(int i = (N<<1)-1; i > 0; --i) {
			if(i >= N) t[i].lo = t[i].md = t[i].hi = i-N;
			else {
				t[i].lo = t[i<<1].lo;
				t[i].md = t[i<<1].hi;
				t[i].hi = t[i<<1|1].hi;
			}
			cout << i << " -> [" << t[i].lo << "," << t[i].hi << "]\n";
		}
		build(A,A+n,1);
	}
};

const int N = 1e5+5;
int A[N],B[N];
unordered_map<int,int> m;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	srand(time(0));
	int n,q;
	cin >> n >> q;
	for(int i = 0; i < n; ++i)
		cin >> A[i];
	wavelet<int> w(A,n);
}