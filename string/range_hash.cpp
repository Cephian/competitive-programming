struct str_hash {
	vector<ll> h,b;
	constexpr static ll B = 37;
	str_hash(const string& s):h(s.size()+1),b(s.size()+1,1) {
		for(int i = 0; i < s.size(); ++i) {
			h[i+1] = h[i]*B+s[i]-'a'+1;
			b[i+1] = b[i]*B;
		}
	}

	//inclusive range hash
	ll hash(int i, int j) {
		return h[j+1] - h[i]*b[j-i+1];
	}
};