//solved in contest
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
 
const int N = 5e5+5;
int A[N];
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	bool r=0;
	int a = N/2;
	int n;
	cin >> n;
	int f=a+1,e=a;
	for(int i = 0; i < n; ++i) {
		if(i&1) cin >> A[--f];
		else cin >> A[++e];
	}
	if(n%2==0) {
		for(int i = f; i <= e; ++i)
			cout << A[i] << " ";
	} else {
		for(int i = e; i >= f; --i)
			cout << A[i] << " ";
	}
	cout << "\n";
}