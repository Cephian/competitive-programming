// sliding window max query
// processes a stream of values, maintining max of the last
// |window| values in O(1)
template <class T>
struct sliding_max {
	int n, ctr = 0;
	deque<pair<T,int>> Q;
	void init(int window) {n = window;}
	sliding_max(int window) {init(window);}

	void add(T a) {
		// for min, change: <= on line below
		while(Q.size() && a >= Q.back().first)
			Q.pop_back();
		Q.emplace_back(a, ++ctr);
	}

	T max() {
		assert(!Q.empty());
		while(Q.front().second <= ctr - n)
			Q.pop_front();
		return Q.front().first;
	}
};
