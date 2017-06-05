#include <iostream>
#include <vector>

using namespace std;

/* persistent segment tree w/ sum query */

struct per_seg {
	vector<int> lc,rc,lx,rx,val,roots = {0};

	//CHANGE ME
	inline int combine(int a, int b) {
		return a+b;
	}

	//build PST on indices i ... j of array a
	int build(int i, int j, int* a) {
		int v = lc.size();
		lc.push_back(-1);
		rc.push_back(-1);
		lx.push_back(i);
		rx.push_back(j);
		val.push_back(a[i]);
		if(i != j) {
			int l = build(i,(i+j)/2,a), r = build((i+j)/2+1,j,a);
			lc[v] = l;
			rc[v] = r;
			val[v] = combine(val[l],val[r]);
		}
		return v;
	}

	int q(int v, int i, int j) {
		if(j < lx[v] || rx[v] < i)
			return 0;
		if(i <= lx[v] && rx[v] <= j)
			return val[v];
		return combine(q(lc[v],i,j),q(rc[v],i,j));
	}

	int u(int v, int i, int a) {
		if(i < lx[v] || rx[v] < i)
			return v;
		int w = lc.size();
		lc.push_back(lc[v]);
		rc.push_back(rc[v]);
		lx.push_back(lx[v]);
		rx.push_back(rx[v]);
		//CHANGE ME
		val.push_back(val[v]+a);
		if(lx[v] != rx[v]) {
			int l = u(lc[v],i,a), r = u(rc[v],i,a);
			lc[w] = l;
			rc[w] = r;
			val[w] = combine(val[l],val[r]);
		}
		return w;
	}

	//sum from i to j after t updates
	int query(int t, int i, int j) {
		return q(roots[t],i,j);
	}

	//add a to position i
	void update(int i, int a) {
		roots.push_back(u(roots.back(),i,a));
	}
};
 
/* USAGE */

int main() {
	int a[5] = {1,1,1,1,1};
	per_seg p;
	p.build(0,4,a);
	p.update(1,1);
	p.update(3,2);
	cout << p.query(2,2,5) << "\n";
	cout << p.query(0,2,5) << "\n";
	cout << p.query(1,0,3) << "\n"	
	return 0;
}