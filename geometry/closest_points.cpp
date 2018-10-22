//return pair<point,point> of two closest points in p
point p[N],strip[N];
typedef pair<point,point> ppp;

double mag(point a) {
	return sqrt(a.x*a.x+a.y*a.y);
}

bool cmp(const pt& a, const pt& b) {
	return a.y < b.y;
}

inline double ds(ppp& p) {
	return (p.first==p.second)?1e200:mag(p.first-p.second);
}

//return pair<point,point> of two closest points
ppp closest(int i, int j) {
	if(i+1 == j)
		return ppp(p[i],p[i]);
	int w = 0, m = (i+j)/2;
	ppp a = closest(i,m),b = closest(m,j);
	if(ds(a) > ds(b)) swap(a,b);
	double d = ds(a);
	for(int l=i; l!=j; ++l)
		if(fabs(p[l].x-p[m].x) < d)
			strip[w++] = p[l];
	sort(strip,strip+w,cmp);
	for(int l = 0; l < w; ++l)
		for(m = min(w-1,l+7);m!=l;--m)
			if(mag(strip[l]-strip[m]) < d)
				a = ppp(strip[l],strip[m]),d=ds(a);
	return a;
}
//if duplicate points, return those
ppp closest(int n) {
	sort(p,p+n);
	for(int i = 1; i < n; ++i)
		if(p[i]==p[i-1])
			return ppp(p[i],p[i]);
	return closest(0,n);
}
