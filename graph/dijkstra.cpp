/* One source, one graph */
template <class T> //weight type
struct ijk {
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

/* multiple sources, one graph
 * each  call to dist() adds another vector to d
 * e.g: if v is the third vertex queried as dist(v), then dist(v,x) = d[2][x]
 * */

template <class T> //weight type
struct ijk {
	typedef pair<T,int> edge;
	typedef vector<vector<edge>> graph;
	typedef priority_queue<edge,vector<edge>,greater<edge>> pq;

	static const T INF = numeric_limits<T>::max();
	graph G;
	vector<vector<T>> d; //distances are stored here
	int N;

	void init(int n) {
		N = n;
		G = graph(n);
	}

	ijk() {}
	ijk(int n) { init(n); }

	void add_edge(int i, int j, T w) {
		G[i].emplace_back(w, j);
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
};
