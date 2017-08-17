#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

set<int> pts;
map<int,int> open;

constexpr int N = 2e5+5;
int n, match[N],ctr=0;
int x[N],y[N],p[N];

int main() {	
	scanf("%d",&n);
	for(int i = 0; i < 2*n; ++i) {
		scanf("%d%d",x+i,y+i);
		p[i] = i;
	}
	sort(p,p+2*n,[=](int i, int j) { return (x[i]!=x[j]) ? x[i]<x[j] : (i/n!=j/n) ? i<j : y[i] < y[j]; });
	bool ok = true;
	for(int i = 0; ok && i < 2*n; ++i) {
		if(p[i] < n) {
			if(open.count(y[p[i]])) ok = false;
			else open[y[p[i]]] = p[i];
		} else {
			auto c = open.upper_bound(y[p[i]]);
			if(c == open.begin()) ok = false;
			else {
				match[(--c)->second] = p[i];
				match[p[i]] = c->second;
				open.erase(c);
			}
		}
	}
	sort(p,p+2*n,[=](int i, int j) { return (x[i]!=x[j]) ? x[i]<x[j] : (i/n!=j/n) ? i < j : y[i] > y[j]; });
	for(int i = 0; ok && i < 2*n; ++i) {
		int a = y[p[i]], b = y[match[p[i]]];
		if(p[i] < n) {
			if(pts.count(a) || pts.count(b)) ok = false;
			else pts.insert(a), pts.insert(b);
			if(a !=b && *pts.upper_bound(a) != b) ok = false;
		} else {
			if(a != b && *pts.upper_bound(b) != a) ok = false;
			else pts.erase(a), pts.erase(b);
		}
	}
	if(ok) for(int i = 0; i < n; ++i)
		printf("%d\n",match[i]+1-n);
	else printf("syntax error\n");
}