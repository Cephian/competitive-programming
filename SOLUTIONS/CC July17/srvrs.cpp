//bad solution -> just samples points randomly and chooses the best one
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
 
struct machine {
	int x,y,p,lt;
	machine(int x, int y, int p):x(x),y(y),p(p),lt(-100000){}
};
 
vector<machine> v;
vector<pii> id;
 
const int N = 500005;
int pos[N];
vector<int> open;
 
constexpr int SEARCH = 70;
 
inline double dist(double a, double b, double c, double d) {
	return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}
 
void swap_open(int i, int j) {
	swap(pos[open[i]],pos[open[j]]);
	swap(open[i],open[j]);
}
 
int select_best(double x, double y) {
	int choice = 0;
	double val = 1e200;
	for(int s = 0; s < min(SEARCH,(int)open.size()); ++s) {
		int q = open.size()-s-1;
		int c = rand()%(q+1);
		swap_open(q,c);
		double vl = dist(x,y,v[open[q]].x,v[open[q]].y)+v[open[q]].p;
		if(vl<val) val=vl,choice=q;
	}
	return choice;
}
 
priority_queue<pii,vector<pii>,greater<pii> > Q;
 
int main() {
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i = 1; i <= n; ++i) {
		int x,y,k,p;
		scanf("%d%d%d",&x,&y,&k);
		for(int j = 1; j <= k; ++j) {
			scanf("%d",&p);
			open.pb(v.size());
			pos[v.size()] = v.size();
			v.emplace_back(x,y,p);
			id.emplace_back(i,j);
		}
	}
 
	int ctr = 0;
	for(int t = 0; t < q; ++t) {
		while(Q.size() && Q.top().fi == t) {
			pos[Q.top().se] = open.size();
			open.pb(Q.top().se);
			// cout << "at time " << t << " adding back " << id[Q.top().se].fi << " " << id[Q.top().se].se << "\n";
			Q.pop();
		}
		printf("?\n"),fflush(stdout);
		int x,y;
		scanf("%d%d",&x,&y);
		int best = select_best(x,y);
		swap_open(best,open.size()-1);
		// cout << "at time " << t << " removing " << id[open.back()].fi << " " << id[open.back()].se << " to be back at " << v[]endl;
		printf("! %d %d\n",id[open.back()].fi,id[open.back()].se),fflush(stdout);
		Q.emplace(t+v[open.back()].p,open.back());
		pos[open.back()] = -1;
		open.pop_back();
		
	}
	printf("end\n"),fflush(stdout);
	
}  