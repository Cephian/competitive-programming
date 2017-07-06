#include <bits/stdc++.h>
using namespace std;

int n,A;
int am = 0;
unordered_set<int> B[1000005];
int where[1000005]={};

const int N = 1e5+5;
int a[N];

int main() {
	scanf("%d%d",&n,&A);

	for(int i = 0; i < n; ++i) {
		scanf("%d",a+i);
		B[0].insert(a[i]);
	}
	B[0].erase(A);
	for(int i = 0; i < n; ++i) {
		if(B[where[a[i]]].count(a[i])) {
			B[where[a[i]]].erase(a[i]);
			++where[a[i]];
			B[where[a[i]]].insert(a[i]);
		}
		if(a[i] == A) {
			B[am++].clear();
		}
	}
	for(int i = 1000000; i >= 0; --i) {
		if(B[i].size()) {
			printf("%d\n",*B[i].begin());
			return 0;
		}
	}
	printf("-1\n");
}