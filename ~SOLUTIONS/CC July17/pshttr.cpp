#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
 
vvi T;
 
struct edge {
	int u,v,c;
	edge(int u, int v, int c):u(u),v(v),c(c){}
	bool operator<(const edge& e) const {
		return c < e.c;
	}
};
 
struct query {
	int u,v,k,i;
	query(int u, int v, int k, int i):u(u),v(v),k(k),i(i){};
	bool operator<(const query& e) const {
		return k < e.k;
	}
};
 
const int N = 1e5+5;
// heavy-light decomposition for general range query structures
// for edge update (u,v), simply update MAX(hld_ind[u],hld_ind[v])
int hld_sz[N], hld_ind[N], hld_parent[N], hld_cstart[N], hld_pr[N], hld_ctr;
 
int hld_fsz(int v, int u = -1) {
	hld_sz[v] = 1;
	for(int w : T[v])
		if(w != u)
			hld_sz[v] += hld_fsz(w,v);
	return hld_sz[v];
}
 
void hld(int v = 0, int u = -1, int head = 0, int d = 0) {
	if(u == -1) hld_ctr=0,hld_fsz(v);
	else hld_parent[hld_ctr] = hld_ind[u];
	hld_cstart[hld_ctr] = head;
	hld_pr[hld_ctr] = d;
	hld_ind[v] = hld_ctr++;
	int lg = -1;
	for(int w : T[v])
		if(w != u && (lg == -1 || hld_sz[w] > hld_sz[lg]))
			lg = w;
	if(lg != -1) hld(lg,v,head,d);
	for(int w : T[v]) {
		if(w == u || w == lg) continue;
		hld(w,v,hld_ctr,d+1);
	}
}
 
//point update, range query, 1-indexed
struct bit {
	vector<int> b;
	bit(int n):b(n+1){};
	inline void update(int i, int v){for(;i<b.size();b[i]^=v,i+=i&-i);}
	int prefix(int i) const {return i?b[i]^prefix(i^(i&-i)):0;}
	inline int query(int l, int r) const {return prefix(r)^prefix(l-1);}
} B(0);
 
//remember to make queries inclusive
int path_query(int u, int v) {
	int x = 0;
	u = hld_ind[u], v = hld_ind[v];
	while(hld_cstart[u] != hld_cstart[v]) {
		if(hld_pr[u] < hld_pr[v]) swap(u,v);
		x ^= B.query(hld_cstart[u]+1,u+1);
		// combine : QUERY [hld_cstart[u], u]
		u = hld_parent[hld_cstart[u]];
	}
	if(u > v) swap(u,v);
	//combine (vert query): QUERY [u,v]
	//combine (edge query): QUERY [u+1,v]
	x ^= B.query(u+2,v+1);
	return x;
}
 
inline void update_edge(int u, int v, int c) {
	int d = max(hld_ind[u],hld_ind[v]);
	B.update(d+1,c);
}
 
vector<edge> E;
vector<query> Q;
int ans[N];
int main() {	
	int t;
	scanf("%d",&t);
	while(t--) {
		int n,m;
		scanf("%d",&n);
		E.clear(),Q.clear();
		T = vvi(n);
		for(int i = 1; i < n; ++i) {
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c),--u,--v;
			E.emplace_back(u,v,c);
			T[u].pb(v),T[v].pb(u);
		}
		scanf("%d",&m);
		for(int i = 0; i < m; ++i) {
			int u,v,k;
			scanf("%d%d%d",&u,&v,&k),--u,--v;
			Q.emplace_back(u,v,k,i);
		}
		sort(E.begin(),E.end());
		sort(Q.begin(),Q.end());
		hld();
		B = bit(n+1);
		int cur = 0;
		for(query &q : Q) {
			while(cur != E.size() && E[cur].c <= q.k) {
				update_edge(E[cur].u,E[cur].v,E[cur].c);
				++cur;
			}
			ans[q.i] = path_query(q.u,q.v);
		}
		for(int i = 0; i < m; ++i) {
			printf("%d\n",ans[i]);
		}
	}
} 