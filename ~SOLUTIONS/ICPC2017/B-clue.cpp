#include <bits/stdc++.h>
using namespace std;

unordered_set<int> p[4];
vector<string> turn,play;
string hand="",s,t;
int hand_sub = 0;
stringstream ss;
int n,tot=0;

void load() {
	getline(cin,s);
	ss = stringstream(s);
}

int bc(int x) {
	int a=0;
	while(x) ++a, x^=x&-x;
	return a;
}

void test(int i, int j) {
	int t = (tot>>i) & ((1<<(j-i))-1);
	if(t^(t&-t)) cout << "?";
	else
		for(int k = i; k < j; ++k)
			if(tot&(1<<k)) {
				cout << char(k+'A');
				return;
			}
}

void search(int pos, int sub, int lo, int j) {
	if(j == -1) {
		for(int i = 0; i < n; ++i) {
			int p1 = i % 4, guess = 0;
			for(int j = 0; j < 3; ++j)
				guess |= 1<<(turn[i][j]-'A'); 
			for(int j = 0; j < play[i].size(); ++j) {
				int p2 = (p1 + j + 1) % 4;
				if(p2 == pos) {
					if(play[i][j] == '-') {
						if(guess&sub) goto bad;
					} else if(play[i][j] == '*') {
						if(!(guess&sub)) goto bad;
					} else {
						if(!(sub & (1<<(play[i][j]-'A')))) goto bad;
					}
				}
			}
		}
		p[pos].insert(sub);
		bad:;
	} else {
		for(int c = lo; c <= 'U'-'A'; ++c)
			if((hand_sub|(1<<c)) != hand_sub)
				search(pos,sub^(1<<c),c+1,j-1);
	}
}

int main() {	
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	load(), n = s[0]-'0';
	if(s.size() == 2) n = n*10 + s[1]-'0';
	load();
	for(int i = 0; i < 5; ++i) {
		ss >> t;
		hand += t;
		hand_sub |= 1<<(t[0]-'A');
	}
	for(int i = 0; i < n; ++i) {
		load();
		s = "";
		for(int i = 0; i < 3; ++i) {
			ss >> t;
			s += t;
		}
		turn.push_back(s), s = "";
		while(ss >> t)
			s += t;
		play.push_back(s);
	}

	search(1,0,0,4);
	search(2,0,0,3);
	search(3,0,0,3);
	for(int a = 0; a < 6; ++a) {
		if(hand_sub & (1<<a)) continue;
		for(int b = 6; b < 12; ++b) {
			if(hand_sub & (1<<b)) continue;
			for(int c = 12; c < 21; ++c) {
				if(hand_sub & (1<<c)) continue;
				int x = (1<<21)-1, sub = (1<<a)|(1<<b)|(1<<c);
				for(int s1 : p[1]) {
					if(sub&s1) continue;
					for(int s2 : p[2]) {
						if(s1&s2 || sub&s2) continue;
						int look = x ^ (hand_sub|sub|s1|s2);
						if(p[3].count(look)) {
							tot |= sub;
							goto end;
						}
					}
				}
				end:;
			}
		}
	}
	test(0,6), test(6,12), test(12,21), cout << "\n";
}