#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct mcmf {
	int N;
	#define BND 1LL<<61
	vector<vector<ll> > cap, fl, cost;
	vector<bool> found;
	vector<ll> dist, pi, width;
	vector<pii> dad;

	mcmf(int N) : 
		N(N), cap(N,vector<ll>(N)), fl(N,vector<ll>(N)), cost(N,vector<ll>(N)), 
		found(N), dist(N), pi(N), width(N), dad(N) {}
	
	void add_edge(int from, int to, ll cap, ll cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
	}
	
	inline void relax(int s, int k, ll cap, ll cost, int dir) {
		ll val = dist[s] + pi[s] - pi[k] + cost;
		if(cap && val < dist[k]) {
			dist[k] = val;
			dad[k] = pii(s, dir);
			width[k] = min(cap, width[s]);
		}
	}

	ll dijkstra(int s, int t) {
		fill(found.begin(),found.end(),0);
		fill(dist.begin(),dist.end(),BND);
		fill(width.begin(),width.end(),0);
		dist[s] = 0;
		width[s] = BND;
		while(s != -1) {
			int best = -1;
			found[s] = true;
			for(int k = 0; k < N; k++) {
				if (found[k]) continue;
				relax(s,k,cap[s][k]-fl[s][k],cost[s][k],1);
				relax(s,k,fl[k][s],-cost[k][s],-1);
				if(best == -1 || dist[k] < dist[best]) best = k;
			}
			s = best;
		}
		for (int k = 0; k < N; k++)
			pi[k] = min(pi[k] + dist[k], BND);
		return width[t];
	}

	pair<ll,ll> flow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while(ll amt = dijkstra(s, t)) {
			totflow += amt;
			for(int x = t; x != s; x = dad[x].first) {
				if(dad[x].second == 1) {
					fl[dad[x].first][x] += amt;
					totcost += amt * cost[dad[x].first][x];
				} else {
					fl[x][dad[x].first] -= amt;
					totcost -= amt * cost[x][dad[x].first];
				}
			}
		}
		return make_pair(totflow,totcost);
	}
};
