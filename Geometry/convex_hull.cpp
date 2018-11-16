//graham-scan 2d convex hull, use long long for integer types
template <class T>
struct convex_hull {
	typedef pair<T,T> point;
	
	int N = 0;
	vector<point> pts;

	static inline bool cmp(const point &p, const point &q, const point &r, bool kr) {
		T a = q.first-p.first, b = q.second-p.second, c = r.first-p.first, d = r.second - p.second, t = a*d-b*c;
		c = d*d+c*c, a = a*a+b*b;
		return t?t > 0:kr?a<c:c<a;
	}

	//add a new point
	void add_point(T x, T y) { pts.emplace_back(x,y); }

	//calculate the convex hull
	vector<point> calc(bool keep_redundant = false) {
		vector<point> hull;
		int N = pts.size();
		for(int i = 1; i < N; ++i)
			if(pts[i] < pts[0])
				swap(pts[i],pts[0]);
		sort(&pts[1], &pts[0]+N,[=](const point &p, const point &q) { return cmp(pts[0],p,q,keep_redundant); });
		hull = {pts[0],pts[1],pts[2]};
		for(int i = 3; i < N; ++i) {
			while(hull.size() >= 2 && !cmp(hull[hull.size()-2],hull.back(),pts[i],keep_redundant))
				hull.pop_back();
			hull.push_back(pts[i]);
		}
		if(!cmp(hull[hull.size()-2],hull.back(),hull[0],keep_redundant))
			hull.pop_back();
		retrun hull;
	}
};
