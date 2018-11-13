//FFT1 for less precise
#include <bits/stdc++.h>
using namespace std;

//USAGE: FFT::fft(A, B) for vector<int> A and B of coefs
// double --> ld is about 30% slower
typedef long double ld;
namespace FFT {
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
			base wlen(cos(ang), sin(ang));
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

	vector<ll> multiply (const vector<int> &a, const vector<int> &b) {
		vector<ll> res;
		vector<base> P(max(a.size(),b.size())),Q;
		for(size_t i = 0; i < a.size(); ++i)
			P[i].re = a[i];
		for(size_t i = 0; i < b.size(); ++i)
			P[i].im = b[i];
		size_t n = 2;
		while ((n>>1) < P.size()) n <<= 1;
		P.resize(n), Q.resize(n);
		fft(&P[0], n, false);
		const base rot(0,-0.25);
		for(size_t i = 0; i != n; ++i) {
			base tmp = P[i?n-i:0].conj();
			Q[i] = (P[i]+tmp)*(P[i]-tmp)*rot;
		}
		fft(&Q[0], n, true);
		res.resize(n);
		for(size_t i = 0; i != n; ++i)
			res[i] = llrint(Q[i].re);
		return res;
	}
}

int main() {
	vector<int> A = {1, -3, 1}    // x^2 - 3x + 1
	vector<int> B = {-7, 2, 0, 2} // -2x^3 + 2x - 7
	vector<ll> C = FFT:multiply(A, B); // higher coefs might be zero
}
