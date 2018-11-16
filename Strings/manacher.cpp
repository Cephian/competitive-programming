//longest palindrome centered at i --> [i-r,i+r] where r = (P[2i+1]-1)/2
//longest palindrome centered between i-1,i --> [i-r,i+r-1] where r = P[2i]/2
void manacher(const string& s, vector<int> &P) {
	int n = s.size(), c = 0;
	string t(2*n+1,'@');
	for(int i = 0; i < n; ++i) t[i<<1|1] = s[i];
	P.resize(t.size());
	for(int i = 1; i < t.size(); ++i) {
		int j = 2*c-i;
		if(j-P[j] > c-P[c])
			P[i] = P[j];
		else {
			P[i] = max(0,c+P[c]-i), c = i;
			while(i+P[i]+1 < t.size() && i-P[i]-1 >= 0 && t[i+P[i]+1] == t[i-P[i]-1])
				++P[i];
		}
	}
}
