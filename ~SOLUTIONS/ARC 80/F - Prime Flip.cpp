#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<int> vi;

struct hopcroft_karp {
	int N,M;
	vector<vector<int>> E;
	vector<int> dist,match,Q;
	hopcroft_karp(int n, int m):N(n),M(m),E(N),dist(N+M),match(N+M,-1),Q(N+M){}

	inline void add_edge(int i, int j) {E[i].push_back(j);}

	bool bfs() {
		fill(&dist[0],&dist[0]+N+M,-1);
		int qf = 0, qb = 0, u;
		bool ok = false;
		for(int i = 0; i < N; ++i)
			if(match[i] == -1)
				Q[qb++] = i, dist[i] = 0;
		while(qf != qb) {
			if((u = Q[qf++]) < N) {
				for(int v : E[u])
					if(dist[N+v] == -1)
						dist[Q[qb++] = N+v] = dist[u] + 1;
			} else {
				if(match[u] == -1) ok = true;
				else if(dist[match[u]] == -1)
					dist[Q[qb++] = match[u]] = dist[u] + 1;
			}
		}
		return ok;
	}

	bool dfs(int u) {
		for(int &i = Q[u]; i < E[u].size(); ++i) {
			int v = N+E[u][i];
			if(dist[v] == dist[u]+1 && (match[v] == -1 || (dist[match[v]] == dist[v]+1 && dfs(match[v])))) {
				match[v] = u, match[u] = v-N;
				return true;
			}
		}
		return false;
	}

	int solve() {
		int ans = 0;
		while(bfs()) {
			fill(&Q[0],&Q[0]+N,0);
			for(int i = 0; i < N; ++i)
				if(match[i] == -1 && dfs(i))
					++ans;
		}
		return ans;
	}
};

const int N = 105, P = 1e7+5;
int a[N]={-1};
bool p[P];
vi odd,evn;

inline void add(int i) {
	((i&1)?odd:evn).pb(i);
}

int main() {
	fill(p,p+P,1);
	p[0] = p[1] = false;
	for(int i = 2; 1LL * i * i < P; ++i)
		if(p[i])
			for(int j = i * i; j < P; j += i)
				p[j] = false;
	p[2] = false;
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i)
		scanf("%d",a+i);
	for(int i = 1; i <= n; ++i) {
		if(a[i-1] != a[i]-1) add(a[i]-1);
		if(a[i+1] != a[i]+1) add(a[i]);
	}
	hopcroft_karp HK(evn.size(), odd.size());
	for(int i = 0; i < evn.size(); ++i)
		for(int j = 0; j < odd.size(); ++j)
			if(p[abs(evn[i]-odd[j])])
				HK.add_edge(i,j);
	int k = HK.solve();
	printf("%d\n",k + int((odd.size()-k)/2*2 + (evn.size()-k)/2*2 + ((odd.size()-k)&1)*3));
}