//solves SPOJ STABLEMP
#include <bits/stdc++.h>
using namespace std;

//male[i][j] is the j-th most desired female for male i
//analogous for female[i][j]
const int N = 505;
int male[N][N],female[N][N],propose[N];
int wife[N],husband[N],tmp[N];
int bachelors[N],bsz=0;
void marry(int n) {
	fill(wife,wife+n,-1);
	fill(husband,husband+n,-1);
	fill(propose,propose+n,0);
	bsz = n;
	for(int i = 0; i < n; ++i) {
		bachelors[i] = i;
		copy(female[i],female[i]+n,tmp);
		for(int j = 0; j < n; ++j)
			female[i][tmp[j]] = j;
	}
	while(bsz) {
		int i = bachelors[--bsz], j = male[i][propose[i]++];
		if(husband[j] == -1)
			wife[i] = j, husband[j] = i;
		else if(female[j][husband[j]] > female[j][i])
			bachelors[bsz++] = husband[j], husband[j] = i, wife[i] = j;
		else
			++bsz;
	}
}
 
int main() {	
	int T;
	scanf("%d",&T);
	while(T--) {
		int n,t;
		scanf("%d",&n);
		for(int i = 0; i < n; ++i) {
			scanf("%d",&t);
			for(int j = 0; j < n; ++j)
				scanf("%d",female[i]+j),--female[i][j];
		}
		for(int i = 0; i < n; ++i) {
			scanf("%d",&t);
			for(int j = 0; j < n; ++j)
				scanf("%d",male[i]+j),--male[i][j];
		}
		marry(n);
		for(int i = 0; i < n; ++i)
			printf("%d %d\n",i+1,wife[i]+1);
	}
} 