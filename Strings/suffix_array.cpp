// O(n log^2 n) suffix array
// return_val[i] is the starting index of the i-th sorted suffix
vector<int> suff_arr(const string& s) {
	const int n = s.size();
	vector<int> source(s.begin(), s.end()), tmp(n), order(n);
	for(int i = 0; i < n; ++i)
		order[i] = i;
	int gap = 0;
	auto cmp = [&](int i, int j) -> bool {
		if(source[i] != source[j])
			return source[i] < source[j];
		const int a = (i+gap >= n) ? -1 : source[i+gap];
		const int b = (j+gap >= n) ? -1 : source[j+gap];
		return a < b;
	};
	for(gap = (n > 1); gap < n; gap += max(1, gap)) {
		sort(order.begin(), order.end(), cmp);
		int ctr = tmp[order[0]] = 0;
		for(int i = 1; i < (int)order.size(); ++i) {
			ctr += cmp(order[i],order[i-1]) || cmp(order[i-1], order[i]);
			tmp[order[i]] = ctr;
		}
		swap(source, tmp);
	}
	return order;
}

// O(n log n) kasai algorithm
// return_val[i] is LCP(suff_arr[i], suff_arr[i+1])
vector<int> lcp_arr(const string& s, const vector<int>& suff_arr) {
	const int n = s.size();
	vector<int> lcp(n), inv(n);
	for(int i = 0; i < n; ++i)
		inv[suff_arr[i]] = i;
	int k = 0;
	for(int i = 0; i < n; ++i) {
		if(inv[i] == n-1) {
			k = 0;
		} else {
			const int j = suff_arr[inv[i]+1];
			while(max(i,j)+k < n && s[i+k] == s[j+k])
				++k;
			lcp[inv[i]] = k;
			k -= (k>0);
		}
	}
	return lcp;
}
