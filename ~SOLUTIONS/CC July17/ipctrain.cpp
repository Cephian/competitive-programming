#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
 
struct trn {
	int d,t,s;
};
 
vector<trn> v;
priority_queue<pii> pq;
 
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n,d;
		scanf("%d%d",&n,&d);
		v.clear();
		for(int i = 0; i < n; ++i) {
			trn t;
			scanf("%d%d%d",&t.d,&t.t,&t.s);
			v.pb(t);
		}
		sort(v.begin(),v.end(),[=](const trn &a, const trn &b) {return a.d < b.d;});
		int cr = 0;
		for(int day = 1; day <= d; ++day) {
			while(cr!=v.size() && v[cr].d == day) {
				pq.push(pii(v[cr].s,v[cr].t));
				++cr;
			}
			if(pq.size()) {
				pii p = pq.top();
				pq.pop();
				if(--p.se != 0)
					pq.push(p);
			}
		}
		ll loss = 0;
		while(pq.size()) {
			pii p = pq.top();
			pq.pop();
			loss += p.fi*1LL*p.se;
		}
		printf("%lld\n",loss);
	}
}