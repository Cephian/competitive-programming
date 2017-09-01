//represents a set of intervals
struct interval_union : set<pii> {
	inline void merge(pii &p, const set<pii>::iterator &q) {
		p.first = min(p.first,q->first), p.second = max(p.second,q->second);
		erase(q);
	}

	//add [l,r]
	//return true if it was merged with some other interval
	bool add(int l, int r) {
		pii p(l,r);
		set<pii>::iterator c;
		bool mrg = false;
		while((c = lower_bound(p)) != end() && c->first <= r)
			merge(p,c), mrg = true;
		if((c = lower_bound(p)) != begin() && (--c)->second >= l)
			merge(p,c), mrg = true;
		insert(p);
		return mrg;
	}
};