#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

const int N=100005;
vpii G[N];
bool vis[N]={0},is_bridge[N]={0};
int lab[N],reach[N],ctr=0;

void bridge(int f, int v) {
	vis[v]=1;
	reach[v]=lab[v]=ctr++;
	for(int i = 0; i < G[v].size(); ++i) {
		int u = G[v][i].first;
		if(u==f) continue;
		if(!vis[u]) {
			bridge(v,u);
			if(reach[u] > lab[v])
				is_bridge[G[v][i].second]=true;
		}
		reach[v] = min(reach[v],reach[u]);
	}
}

int main() {
	ios::sync_with_stdio(0);
	int n,m;
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int u,v;
		cin >> u >> v;
		G[--u].push_back(pii(--v,i));
		G[v].push_back(pii(u,i));
	}
	bridge(-1,0);
	for(int i = 0; i < m; ++i) {
		if(is_bridge[i])
			cout << "edge " << i << " is a bridge\n";
	}
	return 0;
}
