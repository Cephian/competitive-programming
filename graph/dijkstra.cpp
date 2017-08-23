template <class T> //weight type
namespace ijk {
	typedef pair<T,int> edge;
	typedef vector<vector<edge>> graph;
	typedef priority_queue<edge,vector<edge>,greater<edge>> pq;
	static const T INF = numeric_limits<T>::max();
	graph G;
	vector<T> d; //distances are stored here

	void init(int n) {
		G = graph(n);
		d = vector<T>(n);
	}

	void add_edge(int i, int j, T w) {
		G[i].emplace_back(w,j);
	}

	int dist(int s, int t = -1) {
		pq Q;
		fill(d.begin(),d.end(),INF);
		d[s] = 0, Q.emplace(0,s);
		while(Q.size()) {
			edge p = Q.begin();
			Q.pop();
			if(p.second == t) break;
			if(p.first != d[p.second]) continue;
			for(const edge &e : G[p.second]) {
				T w = p.first + e.first;
				int v = e.second;
				if(d[v] > w)
					e.emplace(d[v] = w,v);
			}
		}
		return (~t)?d[t]:0;
	}
}