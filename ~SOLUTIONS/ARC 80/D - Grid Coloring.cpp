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

constexpr int N = 10005,H=100,W=100;

int g[H][W],a[N];

int main() {	
	int h,w,n;
	scanf("%d%d%d",&h,&w,&n);
	for(int i = 1; i <= n; ++i)
		scanf("%d",a+i);
	int cur = 1;
	for(int i = 0; i < h; ++i) {
		int s = (i&1)?0:w-1;
		int e = (i&1)?w:-1;
		int m = (i&1)?1:-1;
		for(int j = s; j != e; j += m) {
			while(a[cur] == 0) ++cur;
			g[i][j] = cur, --a[cur];
		}
	}
	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j)
			printf("%d ",g[i][j]);
		printf("\n");
	}
}