struct suff_arr {
	int n;
	vector<int> A,I;
	
	void build() {
		vector<int> T(n),L(n),F(n+1);
		I = A;
		for(int i = 0; i < n; ++i) L[i] = i;
		A[n] = I[n] = 0;
		sort(L.begin(),L.end(),[this](int i, int j) {return (A[i]!=A[j])?A[i]<A[j]:A[min(i+1,n)]<A[min(j+1,n)];});
		for(int g = 1;;) {
			for(int i = 0; i < n; ++i)
				I[L[i]] = (i && A[L[i]]==A[L[i-1]] && A[min(L[i]+g,n)]==A[min(L[i-1]+g,n)]) ? I[L[i-1]] : i+1;
			if((g <<= 1) < n) {
				fill(F.begin(),F.end(),0);
				F[0] = g;
				for(int i = n-g-1; i >= 0; --i) ++F[I[min(i+g,n)]];
				for(int i = 1; i <= n; ++i) F[i] += F[i-1];
				for(int i = 0; i < n; ++i) T[--F[I[min(i+g,n)]]] = i;
				fill(F.begin(),F.end(),0);
				for(int i = 0; i < n; ++i) ++F[I[i]];
				for(int i = 1; i <= n; ++i) F[i] += F[i-1];
				for(int i = n-1; i >= 0; --i) L[--F[I[T[i]]]] = T[i];
				swap(A,I);
			} else break;
		}
		A.pop_back(); I.pop_back();
		for(int i = 0; i < n; ++i)
			A[--I[i]] = i;
	}

	suff_arr(const int* a, int sz):n(sz),A(n+1) {
		for(int i = 0; i < n; A[i] = a[i]+1,++i);
		build();
	}

	suff_arr(const string& s):n(s.size()),A(s.size()+1) {
		for(int i = 0; i < n; A[i] = s[i]+1,++i);
		build();
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s;
	cin >> s;
	suff_arr S(s);
	for(int i = 0; i < s.size(); ++i)
		cout << S.A[i] << "\n";
	
} 