//repsents the union of intervals
struct interval_union : set<pii> {
	inline void merge(pii &p, set<pii>::iterator q) {
		p.first = min(p.first,q->first), p.second = max(p.second,q->second);
		erase(q);
	}
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

	void remove(int l, int r) { erase(pii(l,r)); }
};