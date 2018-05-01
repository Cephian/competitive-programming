//v[i] is longest prefix of s starting from i
void z_algo(const string &s, vector<int> &Z) {
	int n = s.size(), l = 0, r = 0;
	Z.resize(n);
	for(int i = 1; i < n; ++i) {
		if(i <= r && Z[i-l] < r-i+1)
			Z[i] = Z[i-l];
		else {
			l = i, r = max(r,i);
			while(r < n & s[r-l] == s[r]) ++r;
			Z[i] = r---l;
		}
	}
}