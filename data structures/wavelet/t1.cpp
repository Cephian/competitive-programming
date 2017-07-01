#include <bits/stdc++.h>
using namespace std;

int nm=0;

struct node {
	int lo,hi,md;
	int l,r;
}

struct wavelet_tree{
	#define vi vector<int>
	#define pb push_back
	int lo, hi, mid;
	wavelet_tree *l=0, *r=0;
	vi b;
	 
	//nos are in range [x,y]
	//array indices are [from, to)
	wavelet_tree(int *from, int *to, int x, int y){
		++nm;
		lo = x, hi = y;
		if(lo == hi or from >= to) return;
		mid = floor(((long long)lo+hi)/2.0);
		// cout << "[" << x << "," << y << "] -> " << mid << "\n";
		auto f = [this](int x){
			return x <= mid;
		};
		b.reserve(to-from+1);
		b.pb(0);
		for(auto it = from; it != to; it++)
			b.pb(b.back() + f(*it));
		//see how lambda function is used here
		auto pivot = stable_partition(from, to, f);
		l = new wavelet_tree(from, pivot, lo, mid);
		r = new wavelet_tree(pivot, to, mid+1, hi);
	}

	// wavelet_tree(int* from, int *to):wavelet_tree(from,to,*min_element(from,to),*max_element(from,to)){}
 
	//kth smallest element in [l, r]
	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int inLeft = b[r] - b[l-1];
		int lb = b[l-1]; //amt of nos in first (l-1) nos that go in left
		int rb = b[r]; //amt of nos in first (r) nos that go in left
		if(k <= inLeft) return this->l->kth(lb+1, rb , k);
		return this->r->kth(l-lb, r-rb, k-inLeft);
	}
 
	//count of nos in [l, r] Less than or equal to k
	int LTE(int l, int r, int k) {
		if(l > r or k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = b[l-1], rb = b[r];
		return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
	}
 
	//count of nos in [l, r] equal to k
	int count(int l, int r, int k) {
		if(l > r or k < lo or k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = b[l-1], rb = b[r];
		if(k <= mid) return this->l->count(lb+1, rb, k);
		return this->r->count(l-lb, r-rb, k);
	}
	~wavelet_tree(){
		if(l) delete l;
		if(r) delete r;
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
	for(int i = 0; i < n; ++i) {
		cin >> A[i];
		B[i] = A[i];
	}
	sort(B,B+n);
	for(int i = 0; i < n; ++i)
		m[B[i]] = i;
	for(int i = 0; i < n; ++i) {
		A[i] = m[A[i]];
	}
	wavelet_tree w(A,A+n,0,n);
	while(q--) {
		int i,j,k;
		cin >> i >> j >> k;
		//w.kth(i,j,k);
		cout << B[w.kth(i,j,k)] << "\n";
	}
	// cout << "done\n";
}