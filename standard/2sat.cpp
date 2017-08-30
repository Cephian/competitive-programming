// variables in a clause are represented in the a,b arrays as follows:
// variables range from 0 to n-1.
// a non-negated variable v is 2v+1, negated is 2v

// the formula is (a[0] OR b[0]) AND ... AND (a[c] OR b[c])
// solve_2sat returns whether the formula is satisfiable
// if satisfiable, afterwards ans[v]=1 iff v is true in the satisfying assignment found

//maximum number of distinct variables in your statement
struct two_sat {
	vector<bool> vis = {};
	int cz=0,N;
	vector<int> cc,L,a,b;
	vector<vector<int>> G,R;

	two_sat(){}
	two_sat(int n):N(n),G(2*n),R(2*n),vis(2*n),cc(2*n){}

	void visit(int v) {
		vis[v] = 1;
		for(auto u : G[v])
			if(!vis[v])
				visit(u);
		L.push_back(v);
	}

	inline void assign(int v, int r, vector<bool>& a) {
		if(cc[v]) return;
		cc[v] = r;
		for(auto u : R[v])
			assign(u,r,a);
		a[v/2]=v&1;
	}

	inline void add(int x1, bool v1, int x2, bool v2) {
		x1 = x1<<1|v1, x2 = x2<<1|v2;
		G[x1^1].push_back(x2);
		G[x2^1].push_back(x1);
		R[x1].push_back(x2^1);
		R[x2].push_back(x1^1);
	}

	bool solve(vector<bool>& ans) {
		ans.resize(N);
		for(int i = 0; i < 2*N; ++i)
			if(!vis[i]) visit(i);
		vis = vector<bool>(N);
		for(int i = L.size()-1; i >= 0; --i) {
			if(!cc[L[i]])
				assign(L[i],++cz,ans);
		}
		for(int i = 0; i < N; ++i)
			if(cc[2*i]==cc[2*i+1])
				return false;
		return true;
	}
};