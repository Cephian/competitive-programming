//triangulate a polygon in O(n^2)

bool same_side(point& a, point& b, point& u, point& v) {
	return cross(b-a,u-a)>0 == cross(b-a,v-a)>0;
}

bool is_ear(int i, vector<point>& p, vector<int>& prv, vector<int>& nxt) {
	point& a = p[prv[i]],b = p[i],c = p[nxt[i]];
	if(cross(b-a,c-b) <= 0) return false;
	for(int j = nxt[nxt[i]]; nxt[j] != i; j=nxt[j])
		if(same_side(a,b,c,p[j]) && same_side(b,c,a,p[j]) && same_side(c,a,b,p[j]))
			return false;
	return true;
}

//store the result in r as list of vector<int>
//each entry of r has 3 elements, the indices of the verts of the triangle it represents
void triangulate(vector<vector<int>>& r, vector<int>& p) {
	int n = p.size();
	vector<bool> ear;
	vector<int> nxt,prv;
	for(int i = 0; i < n; ++i) {
		prv.push_back((i+n-1)%n);
		nxt.push_back((i+1)%n);
	}
	for(int i = 0; i < n; ++i)
		ear.push_back(is_ear(i,p,prv,nxt));
	int i = 0;
	while(nxt[i] != prv[i]) {
		if(ear[i]) {
			r.push_back({prv[i],i,nxt[i]});
			nxt[prv[i]] = nxt[i];
			prv[nxt[i]] = prv[i];
			ear[nxt[i]] = is_ear(nxt[i],p,prv,nxt);
			ear[prv[i]] = is_ear(prv[i],p,prv,nxt);
		}
		i = nxt[i];
	}
}
