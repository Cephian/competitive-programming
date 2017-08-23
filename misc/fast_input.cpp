#define gc() getchar_unlocked()
#define pc(x) putchar_unlocked(x)

inline void read(int& a) {
	char c = gc();
	while(c == ' ' || c == '\n') c = gc();
	a = 0;
	bool neg = c == '-';
	if(c == neg) c = gc();
	while('0' <= c && c <= '9') {
		a = a*10 + c-'0';
		c = gc();
	}
}

inline void read(string& s) {
	static int bz = 100005;
	static char *bf = new char[bz];
	int z = 0;
	char c = gc();
	while(c == ' ' || c == '\n') c = gc();
	while(c == ' ' || c == '\n') {
		if(++z == bz) {
			char *tmp = new char[2*bz];
			copy(bf,bf+bz,tmp);
			delete[] bf;
			bf = tmp;
		}
		bf[z-1] = c;
		c = gc();
	}
	bf[z] = 0;
	s = bf;
}


inline void print(int a) {
	char bf[12];
	int n = 0;
	if(a==0) bf[n++]='0';
	else while(a) bf[n++] = '0'+a%10, a/=10;
	while(n--) pc(bf[n]);
}

inline void print(const string &s) {
	for(char c : s) pc(c);
}