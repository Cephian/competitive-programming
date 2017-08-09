#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long double ld;
typedef long long ll;
 
constexpr ll MOD = 1e9+7;
 
const int N = 3e5+5;
typedef complex<ld> base;
const ld PI = 2*acosl(0);
int rev[N];
base wlen_pw[N];
 
void fft (base a[], int n, bool invert) {
	for(int i=0; i<n; ++i)
		if (i < rev[i])
			swap (a[i], a[rev[i]]);
	for(int len=2; len<=n; len<<=1) {
		ld ang = 2*PI/len * (invert?-1:+1);
		int len2 = len>>1;
		base wlen (cosl(ang), sinl(ang));
		wlen_pw[0] = base (1, 0);
		for(int i=1; i<len2; ++i)
			wlen_pw[i] = wlen_pw[i-1] * wlen;
		for(int i=0; i<n; i+=len) {
			base t,
				*pu = a+i,
				*pv = a+i+len2, 
				*pu_end = a+i+len2,
				*pw = wlen_pw;
			for (; pu!=pu_end; ++pu, ++pv, ++pw) {
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}
	if(invert)
		for(int i=0; i<n; ++i)
			a[i] /= n;
}
 
int LAST_REV=-1;
void calc_rev (int n) {
	if(n==LAST_REV) return;
	LAST_REV = n;
	int log_n = 31-__builtin_clz(n);
	for(int i=0; i<n; ++i) {
		rev[i] = 0;
		for(int j=0; j<log_n; ++j)
			if(i & (1<<j))
				rev[i] |= 1<<(log_n-1-j);
	}
}
 
const ll CUT = 1LL<<16;
 
void multiply (const vector<ll> & a, const vector<ll> & b, vector<ll> & res) {
    size_t n = 1;
    while(n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    vector<base> fa1(n), fb1(n), fa2(n), fb2(n);
    for(int i = 0; i < a.size(); ++i) {
    	fa1[i] = base(a[i]/CUT);
    	fa2[i] = base(a[i]%CUT);
    }
    for(int i = 0; i < b.size(); ++i) {
    	fb1[i] = base(b[i]/CUT);
    	fb2[i] = base(b[i]%CUT);
    }
    calc_rev(n);
    fft(&fa1[0],n,false);
    fft(&fa2[0],n,false);
    fft(&fb1[0],n,false);
    fft(&fb2[0],n,false);
 
    vector<base> A(n), B(n), C(n), D(n);
    for(int i = 0; i < n; ++i) {
    	A[i] = fa1[i]*fb1[i];
    	B[i] = fa1[i]*fb2[i];
    	C[i] = fa2[i]*fb1[i];
    	D[i] = fa2[i]*fb2[i];
    }
    fft(&A[0],n,true);
    fft(&B[0],n,true);
    fft(&C[0],n,true);
    fft(&D[0],n,true);
 
    res.resize(n);
    for(size_t i=0; i<n; ++i) {
        res[i] = llround(A[i].real())%MOD*CUT*CUT%MOD
    + (llroundl(B[i].real())%MOD+llround(C[i].real())%MOD)%MOD*CUT
    + llround(D[i].real())%MOD;
    	res[i] %=MOD;
	}
}
 
ll pw(ll a, ll b) {
	if(!b) return 1;
	if(b&1) return a*pw(a,b-1)%MOD;
	ll t = pw(a,b/2);
	return t*t%MOD;
}
 
ll fct[N],ift[N];
void gf() {
	fct[0] = ift[0] = 1;
	for(int i = 1; i < N; ++i)
		fct[i] = fct[i-1]*i%MOD, ift[i] = pw(fct[i],MOD-2);
}
 
void sqrt_shift(const vector<ll> &c, vector<ll> &ans, int a) {
	int n = (int) c.size()-1;
	vector<ll> L(n+1),M(n+1),Q(n+1);
	ll pwa = 1;
	for(int k = 0; k <= n; ++k) {
		L[k] = c[n-k]*fct[2*(n-k)]%MOD;
		M[k] = pwa*ift[2*k]%MOD;
		Q[k] = (pwa=pwa*a%MOD)*ift[2*k+1]%MOD;
	}
	vector<ll> LM,LQ;
	multiply(L,M,LM);
	multiply(L,Q,LQ);
	vector<ll> A0(n+1),A1(n);
	for(int r = 0; r <= n; ++r)
		A0[r] = LM[n-r]%MOD*ift[2*r]%MOD;
	for(int r = 0; r <= n-1; ++r)
		A1[r] = LQ[n-1-r]%MOD*ift[2*r+1]%MOD;
	vector<ll> S0,S1;
	ll a_inv = pw(a,MOD-2);
	multiply(A0,A0,S0);
	multiply(A1,A1,S1);
	ans.resize(2*n+1);
	for(int i = 0; i <= 2*n; ++i) {
		ans[i] = S0[i]%MOD;
		if(0<i && i<2*n) ans[i] = (ans[i] - S1[i-1]%MOD*a_inv)%MOD;
		if(ans[i]<0) ans[i]+=MOD;
	}
}
 
int coef[15];
 
int main() {
	gf();
	int T;
	scanf("%d",&T);
	while(T--) {
		int n;
		scanf("%d",&n);
		for(int i = 0; i < n; ++i)
			scanf("%d",coef+i);
		vector<ll> ans = {MOD-coef[0],1}, tmp;
 
		for(int i = 1; i < n; ++i) {
			sqrt_shift(ans,tmp,coef[i]);
			swap(ans,tmp);
		}
 
		printf("%d\n",1<<n);
			for(int i = 0; i < ans.size(); ++i) {
				printf("%lld",ans[i]);
			if(i+1!=ans.size()) printf(" 0 ");
		}
		printf("\n");
	}
} 