//v[i] is LCP(s, suffix of s starting at i)
vector<int> z_algo(const string &s) {
	int n = s.size(), l = 0, r = 0;
	vector<int> Z(n);
	for(int i = 1; i < n; ++i) {
		if(i <= r && Z[i-l] < r-i+1)
			Z[i] = Z[i-l];
		else {
			l = i, r = max(r,i);
			while(r < n && s[r-l] == s[r]) ++r;
			Z[i] = r---l;
		}
	}
	Z[0] = n;
	return Z;
}
