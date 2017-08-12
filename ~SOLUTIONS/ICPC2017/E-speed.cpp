#include <bits/stdc++.h>
using namespace std;

int n;
double t,d[1005],s[1005];

int main() {	
	scanf("%d%lf",&n,&t);
	double lo = 1e8, hi = 1e8;
	for(int i = 0; i < n; ++i) {
		scanf("%lf%lf",d+i,s+i);
		lo = min(lo,s[i]);
	}
	lo = -lo;
	for(int i = 0; i < 100; ++i) {
		double md = (lo+hi)/2;
		double tot = 0;
		for(int i = 0; i < n; ++i)
			tot += d[i] / (s[i] + md);
		if(tot < t) hi = md;
		else lo = md;
	}
	printf("%.12lf\n",lo);
}