#include <iostream>
#include <algorithm>

using namespace std;

// O(n log n) space, O(1) query RMQ
struct rmq {
	const static int MAXN = 1e5+5, LOGN = 20;
	int l[MAXN][LOGN];

	void build(int* a, int n) {
		for(int i = 0; i < n; ++i)
			l[i][0] = a[i];
		for(int k = 1, p = 1; k < D; ++k, p*=2)
			for(int i = 0; i < n; ++i)
				l[i][k] = (i+p<n)?min(l[i][k-1],l[i+p][k-1]):l[i][k-1];
	}

	int query(int i, int j) {
		int p=0;
		for(;(2<<p) <= j-i+1; ++p);
		return min(l[i][p],l[j-(1<<p)+1][p]);
	}
};

/* USAGE */

rmq r;

int main() {
	int a[5] = {4,7,3,9,1};
	r.build(a,5);
	cout << r.query(1,3) << endl;
	//output: 3
	return 0;
}