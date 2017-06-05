#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

// variables in a clause are represented in the a,b arrays as follows:
// variables range from 0 to k-1.
// a non-negated variable v is 2v+1, negated is 2v

// the formula is (a[0] OR b[0]) AND ... AND (a[c] OR b[c])
// solve_2sat returns whether the formula is satisfiable
// if satisfiable, afterwards ans[v]=1 iff v is true in the satisfying assignment found

//maximum number of distinct variables in your statement
const int MAX_K = 1e5+5;

struct solver_2sat {
	vi L;
	bool vis[MAX_K*2]={0};
	int cc[MAX_K*2]={0},cz=0;
	vvi G,R;

	void visit(int v) {
		if(vis[v]) return;
		vis[v]=1;
		for(auto u : G[v])
			visit(u);
		L.push_back(v);
	}

	void assign(int v, int r, vector<bool>& a) {
		if(cc[v]) return;
		cc[v] = r;
		for(auto u : R[v])
			assign(u,r,a);
		if(vis[v/2]) return;
		vis[v/2]=1;
		a[v/2]=v&1;
	}

	bool solve (vector<int>& a, vector<int>& b, vector<bool>& ans, int k) {
		G = vvi(2*k,vi()),R=vvi(2*k,vi());
		for(int i = 0; i < a.size(); ++i) {
			 G[a[i]^1].push_back(b[i]);
			 G[b[i]^1].push_back(a[i]);
			 R[a[i]].push_back(b[i]^1);
			 R[b[i]].push_back(a[i]^1);
		}
		for(int i = 0; i < 2*k; ++i)
			visit(i);
		fill(vis,vis+k,0);
		for(int i = L.size()-1; i >= 0; --i)
			if(!cc[L[i]])
				assign(L[i],++cz,ans);
		for(int i = 0; i < k; ++i)
			if(cc[2*i]==cc[2*i+1])
				return false;
		return true;
	}
}

/* EXAMPLE USAGE */

//translate (variable, is nonnegated)
inline bool t(int v, bool t) {return 2*v+t;}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	// solve (x0 OR x1) AND (x1 OR ~x2) AND (x2 OR ~x0)
	// output: 0 1 1
	vector<int> a = {t(0,1), t(1,1), t(2,0)};
	vector<int> b = {t(1,1), t(2,0), t(0,1)};
	solver_2sat S;
	vector<bool> ans(3,0);
	if(!S.solve(a,b,ans,3)) cout << "unsatisfiable\n";
	else cout << ans[0] << " " << ans[1] << " " << ans[2] << "\n";
	return 0;
}
