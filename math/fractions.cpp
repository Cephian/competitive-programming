typedef long long ll;

struct frac {
	ll n,d;
	static ll gcd(ll a, ll b) {return b?a:gcd(b,a%b);}
	frac(ll a):n(a),d(1) {}
	frac(ll n, ll d):n(n),d(d) {
		if(d < 0) n = -n, d = -d;
		ll g = gcd(n,d);
		n/=g, d/=g;
	}
};
bool operator==(const frac& f, const frac& g) {return f.n==g.n && f.d==g.d;}
frac operator+(const frac& f, const frac& g) {return frac(f.n*g.d + g.n*f.d,g.d*g.d);}
frac operator-(const frac& f, const frac& g) {return frac(f.n*g.d - g.n*f.d,f.d*g.d);}
frac operator*(const frac& f, const frac& g) {return frac(f.n*g.n,f.d*g.d);}
frac operator/(const frac& f, const frac& g) {return frac(f.n*g.d,f.d*g.n);}

bool operator==(const frac& f, ll a) {return f.n==a && f.d==1;}
frac operator+(const frac& f, ll a) {return frac(f.n + a*f.d,f.d);}
frac operator-(const frac& f, ll a) {return frac(f.n - a*f.d,f.d);}
frac operator*(const frac& f, ll a) {return frac(f.n*a,f.d);}
frac operator/(const frac& f, ll a) {return frac(f.n,f.d*a);}

bool operator==(ll a, const frac& f) {return f==a;}
frac operator+(ll a, const frac& f) {return f+a;}
frac operator-(ll a, const frac& f) {return f-a;}
frac operator*(ll a, const frac& f) {return f*a;}
frac operator/(ll a, const frac& f) {return frac(a*f.d,f.n);}
