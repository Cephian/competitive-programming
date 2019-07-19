// very rough template for Mo's algorithm

inline void add(val) {
	// add val to collection
}

inline void remove(val) {
	// remove val from collection
}

int L = 0, R = 0;
int ask(int l, int r) {
	while(R < r) add(all[R++]);
	while(l < L) add(all[--L]);
	while(r < R) remove(all[--R]);
	while(L < l) remove(all[L++]);
	return ANSWER;
}

const int MAGIC = 400;

struct query {
	int l, r, i;
	bool operator<(const query& q) const {
		if(l/MAGIC == q.l/MAGIC)
			return r < q.r;
		return l < q.l;
	}
};

int main() {
	vector<query> Q;
	// populate Q
	sort(Q.begin(), Q.end());
	for(const auto& qu : Q) {
		ans[qu.i] = ask(qu.l, qu.r);
	}
	for(int i = 0; i < Q.size(); ++i0
		cout << ans[i] << '\n';

}
