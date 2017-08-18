#include <bits/stdc++.h>
using namespace std;
typedef vector<bool> vb;
typedef vector<vb> vvb;

const int N = 500;
char c[N];
int n,m,o=0;
vvb g,t;

inline bool get(vvb &g, int i, int j) {
	if(i < 0 || j < 0 || i >= n || j >= m) return 0;
	return g[i][j];
}

bool prev_val(int i, int j) {
	return get(g,i-1,j-1) ^
		get(t,i-2,j-2) ^ get(t,i-2,j-1) ^ get(t,i-2,j) ^
		get(t,i-1,j-2) ^ get(t,i-1,j-1) ^ get(t,i-1,j) ^
		get(t,i,j-2) ^ get(t,i,j-1);
}

pair<int,int> find_error() {
	int r = 0, c = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j)
			t[i][j] = prev_val(i,j);	
		if(prev_val(i,m) || prev_val(i,m+1)) {
			r = i;
			break;
		}
	}
	for(int j = 0; j < m; ++j) {
		for(int i = 0; i < n; ++i)
			t[i][j] = prev_val(i,j);
		if(prev_val(n,j) || prev_val(n+1,j)) {
			c = j;
			break;
		}
	}
	if(!r && c) r = 1;
	if(!c && r) c = 1;
	return make_pair(r-1,c-1);
}

bool empty(vvb &g) {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(g[i][j]) return false;
	return true;
}

bool reduce() {
	auto p = find_error();
	if(p.first != -1) {
		g[p.first][p.second] = g[p.first][p.second]^1;
		if(empty(g) || find_error().first != -1) {
			g[p.first][p.second] = g[p.first][p.second]^1;
			return false;
		}
	}
	swap(g,t);
	return true;
 }

int main() {
	scanf("%d%d",&m,&n);
	g = t = vvb(n+5,vb(m+5));

	for(int i = 0; i < n; ++i) {
		scanf("%s",c);
		for(int j = 0; j < m; ++j) {
			g[i][j] = c[j] == '#';
		}
	}
	
	n+=5,m+=5;
	while(reduce()) {}
	int mnr=1000,mxr=-1,mnc=1000,mxc=-1;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(!g[i][j]) continue;
			mnr = min(mnr,i);
			mxr = max(mxr,i);
			mnc = min(mnc,j);
			mxc = max(mxc,j);
		}
	}
	for(int i = mnr; i <= mxr; ++i) {
		for(int j = mnc; j <= mxc; ++j) {
			if(g[i][j]) printf("#");
			else printf(".");
		}
		printf("\n");
	}
}