#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi T;

struct lca {
	const static int N = 100005,LOGN = 21;
	int depth[N];
	int table[N][LOGN];
	void fill_dfs(const vvi& T, int f, int v, int d) {
		depth[v] = d;
		table[v][0] = f;
		for(int i = 0; i < T[v].size(); ++i) {
			if(T[v][i] == f) continue;
			fill_dfs(T,v,T[v][i],d+1);
		}
	}

	void build_table(int n) {
		for(int k = 1; k < LOGN; ++k)
			for(int i = 0; i < n; ++i)
				table[i][k] = table[table[i][k-1]][k-1];
	}

	void build(const vvi& T, int root) {
		fill_dfs(T,root,root,0);
		build_table(T.size());
	}

	int query(int u, int v) {
		if(depth[u] < depth[v]) swap(u,v);
		for(int l = LOGN-1; l >= 0; --l)
			if((1<<l) <= depth[u]-depth[v])
				u = table[u][l];
		if(u == v) return u;
		for(int l = LOGN-1; l >= 0; --l) {
			if(table[u][l] != table[v][l]) {
				u = table[u][l];
				v = table[v][l];
			}
		}
		return table[u][0];
	}
};

/* USAGE */

lca L;

int main() {
	ios::sync_with_stdio(0);
	// read tree T rooted at 0
	L.build(T,0);
	// call L.query(a,b)
	return 0;
}
