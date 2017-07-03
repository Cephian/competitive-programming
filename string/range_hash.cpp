//query polynomial hash of substring [l,r] of s
struct str_hash32 {
	vector<int> h,b;
	constexpr static int BASE = 37, MOD = 1e9+9;
	str_hash32(const string& s):h(s.size()+1),b(s.size()+1,1) {
		for(int i = 0; i < s.size(); ++i) {
			h[i+1] = (1LL*h[i]*BASE+s[i]-'a'+1)%MOD;
			b[i+1] = (1LL*b[i]*BASE)%MOD;
		}
	}

	//inclusive range hash
	int hash(int i, int j) {
		int r = (h[j+1] - 1LL*h[i]*b[j-i+1])%MOD;
		return (r<0)?r+MOD:r;
	}
};

// change of collision about 1/1e18
struct str_hash64 {
	vector<int> h1,h2,b1,b2;
	const static int BASE=37, M1=1e9+7, M2 = 1e9+9;
	str_hash64(const string &s):h1(s.size()+1),h2(s.size()+1),b1(s.size()+1,1),b2(s.size()+1,1) {
		for(int i = 0; i < s.size(); ++i) {
			h1[i+1] = (1LL*h1[i]*BASE+s[i]-'a'+1)%M1;
			h2[i+1] = (1LL*h2[i]*BASE+s[i]-'a'+1)%M2;
			b1[i+1] = (1LL*b1[i]*BASE)%M1;
			b2[i+1] = (1LL*b2[i]*BASE)%M2;
		}
	}

	//inclusive range hash
	ll hash(int i, int j) {
		ll r1 = (h1[j+1] - 1LL*h1[i]*b1[j-i+1])%M1;
		ll r2 = (h2[j+1] - 1LL*h2[i]*b2[j-i+1])%M2;
		return ((r1<0)?r1+M1:r1) ^ ((r2<0)?r2+M2:r2)<<32;
	}
};
