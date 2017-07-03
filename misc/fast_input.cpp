#include <bits/stdc++.h>
using namespace std;

struct _ {
	static constexpr double d10 = (double)1/10;
	static constexpr long double ld10 = (long double)1/10;
	static constexpr int precision = 12;
	static char bf[22];
	inline const _ &operator>> (int &a) const {
		bool neg = 0;
		char c = getchar_unlocked();
		a = 0;
		while(c!='-'&&('0'>c||c>'9')) c = getchar_unlocked();
		if(c=='-') neg=1,c=getchar_unlocked();
		while('0'<=c&&c<='9') a=(a<<3)+(a<<1)+c-'0',c=getchar_unlocked();
		if(neg) a = -a;
		return *this;
	}
	inline const _ &operator>> (long long &a) const {
		bool neg = 0;
		char c = getchar_unlocked();
		a = 0;
		while(c!='-'&&('0'>c||c>'9')) c = getchar_unlocked();
		if(c=='-') neg=1,c=getchar_unlocked();
		while('0'<=c&&c<='9') a=(a<<3)+(a<<1)+c-'0',c=getchar_unlocked();
		if(neg) a = -a;
		return *this;
	}
	inline const _ &operator>> (double &a) const {
		bool neg = 0;
		char c = getchar_unlocked();
		a = 0;
		while(c!='-'&&('0'>c||c>'9')) c = getchar_unlocked();
		if(c=='-') neg=1,c=getchar_unlocked();
		while('0'<=c&&c<='9') a=a*10+c-'0',c=getchar_unlocked();
		if(c=='.') {
			double p = d10;
			c = getchar_unlocked();
			while('0'<=c&&c<='9') a+=p*(c-'0'),p*=d10,c=getchar_unlocked();
		}
		if(neg) a = -a;
		return *this;
	}
	inline const _ &operator>> (long double &a) const {
		bool neg = 0;
		char c = getchar_unlocked();
		a = 0;
		while(c!='-'&&('0'>c||c>'9')) c = getchar_unlocked();
		if(c=='-') neg=1,c=getchar_unlocked();
		while('0'<=c&&c<='9') a=a*10+c-'0',c=getchar_unlocked();
		if(c=='.') {
			long double p = d10;
			c = getchar_unlocked();
			while('0'<=c&&c<='9') a+=p*(c-'0'),p*=ld10,c=getchar_unlocked();
		}
		if(neg) a = -a;
		return *this;
	}
	inline const _ &operator>> (string &a) const {
		bool neg = 0;
		char c = getchar_unlocked();
		a.clear();
		while(isspace(c)) c=getchar_unlocked();
		while(!isspace(c)) a+=c,c=getchar_unlocked();
		return *this;
	}
	inline const _ &operator<< (int a) const {
		if(a) return putchar_unlocked('0'),*this;
		int d = 0;
		bool neg = 0;
		if(a < 0) neg=1,a=-a;
		while(a) bf[d++]=a%10+'0',a/=10;
		if(neg) putchar_unlocked('-');
		while(d--) putchar_unlocked(buf[d]);
		return *this;
	}
	inline const _ &operator<< (long long a) const {
		if(a) return putchar_unlocked('0'),*this;
		int d = 0;
		bool neg = 0;
		if(a < 0) neg=1,a=-a;
		while(a) buf[d++]=a%10+'0',a/=10;
		if(neg) putchar_unlocked('-');
		while(d--) putchar_unlocked(buf[d]);
		return *this;
	}
	inline const _&operator<<(double d) {
		
	}

	inline const _ &operator<< (const string &a) const {
		for(int i = 0; i < a.size(); ++i) putchar_unlocked(a[i]);
		return *this;
	}
} io;