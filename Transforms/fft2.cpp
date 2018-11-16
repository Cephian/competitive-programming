//FFT2 for more precise
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace FFT {
	typedef long double ld;
	struct base {
		ld re,im;
		base(ld r=0, ld i=0):re(r),im(i){}
		inline base operator*(const base& b) const {
			return base(re*b.re-im*b.im,re*b.im+b.re*im);
		}
		inline base operator-(const base& b) const {
			return base(re-b.re,im-b.im);
		}
		inline base operator+(const base& b) {
			return base(re+b.re,im+b.im);
		}
		inline void operator+=(const base& b) {
			re += b.re, im += b.im;
		}
		inline void operator*=(const base& b) {
			ld r = re;
			re = re*b.re-im*b.im;
			im = r*b.im+b.re*im;
		}
		inline void operator/=(int b) {
			re /= b;
			im /= b;
		}
		inline base operator/(int b) const {
			return base(re/b,im/b);
		}
		inline base conj() const {
			return base(re,-im);
		}
	};

	vector<int> rev;
	vector<base> wlen_pw;
	void fft(base a[], int n, bool invert) {
		static int last_n = 0;
		static const ld two_pi = acosl(0)*4;
		if(n != last_n) {
			if(n > last_n) rev.resize(n), wlen_pw.resize(n);
			last_n = n;
			int log_n = 31-__builtin_clz(n);
			for(int i = 0; i < n; ++i) {
				rev[i] = 0;
				for(int j = 0; j < log_n; ++j)
					if(i & (1<<j))
						rev[i] |= 1<<(log_n-1-j);
			}
		}
		for(int i = 0; i < n; ++i)
			if(i < rev[i])
				swap(a[i], a[rev[i]]);
		for(int len=2; len<=n; len<<=1) {
			ld ang = two_pi/len * (invert?-1:+1);
			int len2 = len>>1;
			base wlen(cosl(ang), sinl(ang));
			wlen_pw[0] = base(1);
			for(int i = 1; i < len2; ++i)
				wlen_pw[i] = wlen_pw[i-1] * wlen;
			for(int i = 0; i < n; i += len) {
				base t, *pu = a+i, *pv = a+i+len2, 
					*pu_end = a+i+len2, *pw = &wlen_pw[0];
				for(; pu!=pu_end; ++pu, ++pv, ++pw)
					t = *pv * *pw, *pv = *pu - t, *pu += t;
			}
		}
		if(invert)
			for(int i=0; i<n; ++i)
				a[i] /= n;
	}

	void multiply(const vector<ll> &a, const vector<ll> &b, vector<ll> &res) {
		vector<base> P(max(a.size(),b.size())),Q;
		for(int i = 0; i < a.size(); ++i)
			P[i].re = a[i];
		for(int i = 0; i < b.size(); ++i)
			P[i].im = b[i];
		size_t n = 2;
		while ((n>>1) < P.size()) n <<= 1;
		P.resize(n), Q.resize(n);
		fft(&P[0], n, false);
		for(size_t i = 0; i != n; ++i) {
			base tmp = P[i?n-i:0].conj();
			Q[i] = (P[i]+tmp)*(P[i]-tmp)*base(0,-0.25);
		}
		fft(&Q[0], n, true);
		res.resize(n);
		for(size_t i = 0; i != n; ++i)
			res[i] = llround(Q[i].re);
	}

	void multiply_mod(const vector<ll> a, const vector<ll> b, vector<ll> &res, ll M) {
		ll S = 1LL<<16;
		vector<base> P_a(a.size()), P_b(b.size()),Q1,Q2;
		for(int i = 0; i < a.size(); ++i)
			P_a[i].re = a[i]&(S-1), P_a[i].im = a[i]>>16;
		for(int i = 0; i < b.size(); ++i)
			P_b[i].re = b[i]&(S-1), P_b[i].im = b[i]>>16;
		size_t n = 2;
		while ((n>>1) < max(a.size(),b.size())) n <<= 1;
		P_a.resize(n), P_b.resize(n), Q1.resize(n), Q2.resize(n), res.resize(n);
		fft(&P_a[0],n,false), fft(&P_b[0],n,false);
		for(size_t i = 0; i != n; ++i) {
			base ta = P_a[i?n-i:0].conj();
			base tb = P_b[i?n-i:0].conj();
			base a_lo = (P_a[i]+ta)*base(0.5);
			base a_hi = (P_a[i]-ta)*base(0,-0.5);
			base b_lo = (P_b[i]+tb)*base(0.5);
			base b_hi = (P_b[i]-tb)*base(0,-0.5);
			Q1[i].re = a_lo*b_lo;
			Q1[i].im = a_hi*b_hi;
			Q2[i].re = a_lo*b_hi;
			Q2[i].im = a_hi*b_lo;
		}
		fft(&Q1[0],n,true), fft(&Q2[0],n,true);
		for(size_t i = 0; i != n; ++i) {
			base t1 = Q1[i?n-i:0].conj();
			base t2 = Q2[i?n-i:0].conj();
			base c_ll = (Q1[i]+ta)*base(0.5);
			base c_hh = (Q1[i]-ta)*base(0,-0.5);
			base c_lh = (Q2[i]+tb)*base(0.5);
			base c_hl = (Q2[i]-tb)*base(0,-0.5);
			res[i] = (llround(c_ll)%M + ((llround(c_lh)%M + llround(c_hl)%M)<<16)%M + ((llround(c_hh)%M)<<32)%M)%M;
		}
	}
}

int main() {
	int T,n;
	scanf("%d",&T);
	for(int t = 0; t < T; ++t) {
		vector<ll> A,B,ans;
		int a,b;
		scanf("%d",&a);
		A.resize(a+1);
		for(int k = 0; k <= a; ++k)
			scanf("%lld",&A[k]);
		scanf("%d",&b);
		B.resize(b+1);
		for(int k = 0; k <= b; ++k)
			scanf("%lld",&B[k]);
		FFT::multiply(A,B,ans);
		while(ans.size() && !ans.back())
			ans.pop_back();
		printf("%d\n",(int)ans.size()-1);
		for(int i = 0; i < ans.size(); ++i)
			printf("%lld ",ans[i]);
		printf("\n");

	}
}