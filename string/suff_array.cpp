// efficient n log^2 n suffix array
// remember to set n = s.size()

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int N = 100005,LOGN=17;
int suff_arr[N+1],tmp[N+1],L[N],gap,n;
string s;

bool cmp(int i, int j) {
	if(suff_arr[i] != suff_arr[j]) return suff_arr[i] < suff_arr[j];
	return suff_arr[min(i+gap,n)] < suff_arr[min(j+gap,n)];
}

void build_sa() {
	suff_arr[n] = tmp[n] = -1;
	for(int i = 0; i < n; ++i) {
		suff_arr[i] = s[i];
		L[i]=i;
	}
	gap=1;
	while(gap < n) {
		sort(L,L+n,cmp);
		for(int i = 0; i < n; ++i)
			tmp[L[i]] = (i && !cmp(L[i],L[i-1]) && !cmp(L[i-1],L[i])) ? tmp[L[i-1]] : i;
		swap(suff_arr,tmp);
		gap*=2;
	}
}

//lcp[i] stores LCP(suff_arr[i], suff_arr[i+1])
int lcp[N],inv[N];
void kasai() {
	int k = 0;
	for (int i = 0; i < n; ++i)
		suff_arr[inv[i]] = i;
	for (int i = 0; i < n; ++i) {
		if(inv[i] == n-1) {
			k = 0;
			continue;
		}
		int j = inv[suff_arr[i]+1];
		while(i+k<n && j+k<n && s[i+k]==s[j+k])
			++k;
		lcp[suff_arr[i]] = k;
		k -= k > 0;
	}
}

int main() {
	ios::sync_with_stdio(0);
	s = "banana";
	n = s.size();
	build_sa();
	build_lcp();
	for(int i = 0; i < n; ++i)
		cout << inv[i] << " -> " << s.substr(inv[i],n-inv[i]) << " " << lcp[i] << "\n";
	return 0;
}
