// a MIN sliding window
template <class T>
struct sliding_window {
	int ctr = 0, K = -1;
	deque<pair<T,int>> data;
	void init(int k){K = k;}
	sliding_window(int k){init(k);}
	sliding_window() {}

	// add an element and return the result for current window
	T add(T nxt) {
		assert(K != -1);
		// flip to below >= for MAX
		while(data.size() && nxt <= data.back().first)
			data.pop_back();
		data.emplace_back(nxt, ctr);
		if(data.size() && data.front().second + K == ctr)
			data.pop_front();
		++ctr;
		return data.front().first;
	}
};
