struct eval_link {
	typedef pair<int,int> pii;
	void init(int n) {
		parent.assign(n + 1, 0);
		child.assign(n + 1, 0);
		size.assign(n + 1, 1);
		size[0] = 0;
		min.resize(n + 1);
	}
 
	void set(int v, const pii &val) {
		min[v + 1] = val;
	}
 
	pii eval(int v) {
		++v;
		if(parent[v] == 0)
			return min[v];
		compress(v);
		return std::min(min[parent[v]], min[v]);
	}
 
	void link(int v, int w) {
		++v, ++w;
		assert(parent[w] == 0);
		int s = w;
		while(min[w] < min[child[s]]) {
			if(size[s] + size[child[child[s]]] >= 2 * size[child[s]]) {
				parent[child[s]] = s;
				child[s] = child[child[s]];
			} else {
				size[child[s]] = size[s];
				s = parent[s] = child[s];
			}
		}
		min[s] = min[w];
		size[v] = size[v] + size[w];
		if(size[v] < 2 * size[w])
			swap(s, child[v]);
		while(s != 0) {
			parent[s] = v;
			s = child[s];
		}
	}
 
	void compress(int v) {
		assert(parent[v] != 0);
		if(parent[parent[v]] != 0) {
			compress(parent[v]);
			if(min[parent[v]] < min[v])
				min[v] = min[parent[v]];
			parent[v] = parent[parent[v]];
		}
	}
 
	vector<int> parent, child, size;
	vector<pii> min;
};
 
struct dominator_tree {
	void init(int n){graph.resize(n);}
	dominator_tree(int n) {init(n);}

	void add_edge(int u, int v) {
		graph[u].push_back(v);
	}

	//build dominator tree after adding edges
	void build(int root) {
		step1(graph, root);
		step2and3(graph, root);
		step4();
	}
 
 	//get dominator of node u (after build)
	int get_dom(int u) const { return dom[u]; }
 
	void step1(const vector<vector<int>> &graph, int root) {
		pred.assign(graph.size(), vector<int>());
		semi.assign(graph.size(), -1);
		parent.assign(graph.size(), -1);
		vertex.clear();
		stk.emplace_back(root, 0);
		while(!stk.empty()) {
			int v = stk.back().first;
			int ei = stk.back().second;
			stk.pop_back();
			if(ei == 0) {
				semi[v] = (int)vertex.size();
				vertex.push_back(v);
			}
			if(ei != graph[v].size()) {
				stk.emplace_back(v, ei + 1);
				int w = graph[v][ei];
				if(semi[w] == -1) {
					parent[w] = v;
					stk.emplace_back(w, 0);
				}
				pred[w].push_back(v);
			}
		}
	}
 
	void step2and3(const vector<vector<int>> &graph, int root) {
		bucket.assign(graph.size(), vector<int>());
		dom.assign(graph.size(), -1);
		evalLink.init((int)graph.size());
		for(int w : vertex)
			evalLink.set(w, make_pair(semi[w], w));
		for(int i = (int)vertex.size() - 1; i > 0; -- i) {
			int w = vertex[i];
			for(int v : pred[w]) {
				int u = evalLink.eval(v).second;
				if(semi[u] < semi[w])
					semi[w] = semi[u];
			}
			evalLink.set(w, make_pair(semi[w], w));
			bucket[vertex[semi[w]]].push_back(w);
			evalLink.link(parent[w], w);
			for(int v : bucket[parent[w]]) {
				int u = evalLink.eval(v).second;
				dom[v] = semi[u] < semi[v] ? u : parent[w];
			}
		}
	}
 
	void step4() {
		for(int i = 1; i < (int)vertex.size(); ++ i) {
			int w = vertex[i];
			if(dom[w] != vertex[semi[w]])
				dom[w] = dom[dom[w]];
		}
		dom[vertex[0]] = -1;
	}
 
	vector<int> parent;
	vector<vector<int>> pred;
	vector<vector<int>> graph;
	vector<int> semi;
	vector<int> vertex;
	vector<vector<int>> bucket;
	vector<int> dom;
	vector<pair<int,int>> stk;
	eval_link evalLink;
};