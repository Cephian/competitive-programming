#include <iostream>
#include <iomanip>
using namespace std;
typedef long long ll;

inline void read(int &a) {
	bool s = false;
	a = 0;
	while(char c = getchar_unlocked()) {
		if(c==' ' || c=='\n') {
			if(s) return;
		} else {
			s = true;
			a = (a<<3)+(a<<1)+c-'0';
		}
	}
}

inline void read(ll &a) {
	bool s = false;
	a = 0;
	while(char c = getchar_unlocked()) {
		if(c==' ' || c=='\n') {
			if(s) return;
		} else {
			s = true;
			a = (a<<3)+(a<<1)+c-'0';
		}
	}
}

inline void read(string &a) {
	bool s = false;
	a = "";
	while(char c = getchar_unlocked()) {
		if(c==' ' || c=='\n') {
			if(s) return;
		} else {
			s = true;
			a += c;
		}
	}
}

inline void read(double &a) {
	bool s = false,dp = false;
	a = 0;
	double p = 1;
	while(char c = getchar_unlocked()) {
		if(c==' ' || c=='\n') {
			if(s) return;
		} else {
			s=true;
			if(c=='.') {
				dp=true;
			} else if(dp) {
				a += (p*=0.1)*(c-'0');
			} else {
				a = a*10+c-'0';
			} 
		}
	}
}

inline void read(long double &a) {
	bool s = false,dp = false;
	a = 0;
	long double p = 1;
	while(char c = getchar_unlocked()) {
		if(c==' ' || c=='\n') {
			if(s) return;
		} else {
			s=true;
			if(c=='.') {
				dp=true;
			} else if(dp) {
				a += (p*=0.1)*(c-'0');
			} else {
				a = a*10+c-'0';
			} 
		}
	}
}

int main() {
	double d;
	read(d);
	cout << setprecision(12) << fixed << d << endl;
	return 0;
}