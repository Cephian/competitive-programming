#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define fio ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

// O(n log n) space, O(1) index query RMQ
struct rmq_ind {
	vector<vector<int> > t;
	int *A;
	rmq_ind(){}
	rmq_ind(int* a, int n):t(32-__builtin_clz(n),vector<int>(n)) {
		A = a;
		for(int i = 0; i < n; ++i)
			t[0][i] = i;
		for(int k = 1, p = 1; k < t.size(); ++k, p<<=1)
			for(int i = 0; i < n; ++i)
				t[k][i] = (i+p<n && a[t[k-1][i+p]] < a[t[k-1][i]])?t[k-1][i+p]:t[k-1][i];
	}
	//inclusive min query
	inline int query(int l, int r) const {
		int p = 31-__builtin_clz(r-l+1), i = t[p][l], j = t[p][r+1-(1<<p)];
		return (A[i]<A[j])?i:j;
	}
};

const int N = 2e5+5;
int evn[N],odd[N],A[N],n,sz=0;

rmq_ind E,O;
vi children[N];
pii data[N];

vector<int> ans;

int solve(int i, int j) {
	int id = sz++,a = ((i&1)?O:E).query(i,j),b = ((i&1)?E:O).query(a+1,j);
	data[id] = pii(A[a],A[b]);
	if(i != a) children[id].pb(solve(i,a-1));
	if(a+1 != b) children[id].pb(solve(a+1,b-1));
	if(b != j) children[id].pb(solve(b+1,j));
	return id;
}

constexpr int INF = 1<<20;
struct cmp {
	bool operator ()(int i, int j) {
		return data[i] > data[j];
	}
};
priority_queue<int,vector<int>,cmp> Q;

int main() {
	scanf("%d",&n);
	for(int i = 0; i < n; ++i) {
		scanf("%d",A+i);
		if(i&1) odd[i] = A[i], evn[i] = INF;
		else evn[i] = A[i], odd[i] = INF;
	}
	E = rmq_ind(evn,n);
	O = rmq_ind(odd,n);
	solve(0,n-1);
	Q.push(0);
	while(Q.size()) {
		int t = Q.top(); Q.pop();
		ans.pb(data[t].fi), ans.pb(data[t].se);
		for(int j : children[t])
			Q.push(j);
	}
	for(int i = 0; i < n; ++i)
		printf("%d ",ans[i]);
	printf("\n");
}