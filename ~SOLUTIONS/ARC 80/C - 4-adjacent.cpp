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

int b,a[4]={},n;
vector<int> v;

int main() {	
	scanf("%d",&n);
	for(int i = 0; i < n; ++i) {
		scanf("%d",&b);
		++a[b%4];
	}
	a[1] += a[3];
	bool ls = 0;
	while(a[0] + a[1] + a[2]) {
		if(a[0] + a[1]) {
			if(a[0] && a[1]) {
				ls  = !ls;
				v.pb(ls);
				--a[ls];
			} else if(a[0])
				v.pb(0),--a[0];
			else
				v.pb(1),--a[1];
		} else {
			v.pb(2),--a[2];
		}
	}
	for(int i = 1; i < n; ++i) {
		if(v[i] * v[i-1] % 4 != 0) {
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
}