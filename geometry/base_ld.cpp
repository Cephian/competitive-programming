typedef long double ld;
constexpr ld EPS = 1e-10;
struct point { 
	ld x, y; 
	point(){}
	point(ld x, ld y) : x(x), y(y) {}
	point operator + (const point &p) const { return point(x+p.x, y+p.y); }
	point operator - (const point &p) const { return point(x-p.x, y-p.y); }
	point operator * (ld c) const { return point(x*c, y*c); }
	point operator / (ld c) const { return point(x/c, y/c); }
	bool operator == (const point &p) const { return fabsl(x-p.x) + fabsl(y-p.y) < EPS; }
	bool operator < (const point &p) const { return (x==p.x) ? y<p.y : x<p.x; }
};

ostream& operator<<(ostream &o, const point &p) {
	return o << "(" << p.x << "," << p.y << ")",o;
}

ld dot(point p, point q) { return p.x*q.x + p.y*q.y; }
ld cross(point p, point q) { return p.x*q.y - p.y*q.x; }
ld norm(point p) { return p.x*p.x + p.y*p.y; }
ld mag(point p) { return sqrtl(p.x*p.x + p.y*p.y); }
ld dist(point p, point q) { return mag(p - q); }
ld sq_dist(point p, point q) { return norm(p - q) }

// +------------------------------------------------+
// |               LINES AND SEGMENTS               |
// +------------------------------------------------+

//closest point to p on line (a,b)
point projectPL(point p, point a, point b) {
	return a + (b-a) * dot(p-a, b-a) / norm(b-a);
}

//how far along (a,b) is p? (projected)
//0 -> at a, 1 -. at b
ld project_scale(point p, point a, point b) {
	return dot(p-a, b-a) / norm(b-a);
}

//how far along (a,b) is p? (projected)
// 0 -> at a, |b-a| -> at b 
ld project_dist(point p, point a, point b) {
	return dot(p-a, b-a) / mag(b-a);
}

//closest point to p on segment (a,b)
point projectPS(point p, point a, point b) {
	if (a == b) return a;
	ld r = dot(p-a, b-a) / dot(a-b, a-b);
	if (r < 0) return a;
	if (r > 1) return b;
	return a + (b-a)*r;
}

//reflect p over line (a,b)
point reflectPL(point p, point a, point b){
	return (a + (b-a)*dot(p-a, b-a)/norm(b-a))*2 - p;
}

//is p on line (a,b) ?
bool onPL(point p, point a, point b){
	return fabsl(cross(p-a, b-a)) < EPS;
}

//is p on segment (a,b) ?
bool onPS(point p, point a, point b){
	return fabsl(cross(a-p, b-p)) < EPS && (a<p != b<p || p==a || p==b);
}

// are lines (a,b) and (c,d) parallel?
bool parallelLL(point a, point b, point c, point d) { 
  return fabsl(cross(b-a,d-c)) < EPS; 
}

// are lines (a,b) and (c,d) equal?
bool equalLL(pt a, pt b, pt c, pt d) { 
  return onPL(c,a,b) && onPL(d,a,b) && onPL(a,c,d) && onPL(b,c,d);
}

//p -> a -> b: -1 = Clockwise, 0 = Colinear, 1 = Counterclockwise
//p with a->b: -1 = Left, 0 = On, 1 = Right 
int sidePL(point p, point a, point b) {
	ld d = cross(p-a,b-a);
	if(fabsl(d) < EPS) return 0;
	return (d<0)?-1:1;
}

//does segment (a,b) intersect line (c,d) ?
bool intersectSL(point a, point b, point c, point d){
	ld x = cross(a-c,a-d), y = cross(b-c,b-d);
	return x == 0 || y == 0 || (x<0) != (y<0);
}

//do segments (a,b) and (c,d) intersect?
int intersectSS(point a, point b, point c, point d) {
	if(equalLL(a,b,c,d)) {
		if(b < a) swap(a, b);
		if(d < c) swap(c, d);
		if(c < a) swap(a, c), swap(b, d);
		if(c == b || (c == d && c < b)) return 2; //POINT
		else if(c < b) return 1; //SEGMENT
		else return 0; //NONE
	}
	else if(intersectSL(a,b,c,d) && intersectSL(c,d,a,b))
		return 2; //POINT
	else return 0; //NONE
}

//intersection point of distinct lines (a,b) and (c,d)
point intersectLL(point a, point b, point c, point d) {
  return a + (b-a)*(cross(c-a, c-d))/(cross(b-a, c-d));
}

//return perpendicular to (a,b) through midpoint
pair<point,point> perpendicularS(point a, point b) {
	ld m = (a.x + b.x + a.y + b.y)/2;
	return make_pair(point(m-b.y, m-a.x), point(m-a.y, m-b.x));
}

//return perpendicular to (a,b) through p
pair<point,point> perpendicularPL(point p, point a, point b){
	return make_pair(p, a + (b-a)*dot(p-a, b-a)/norm(b-a));
}

point rotate90CC(point p) {
	return point(-p.y,p.x);
}

// +------------------------------------------------+
// |                CIRCLES AND ARCS                |
// +------------------------------------------------+

//center of arc with radius r through p and q
point centerA(point p, point q, ld r) {
	point m = (p+q)/2;
	auto l = perpendicularS(p,q);
	ld d = sqrtl(r*r - norm(b-a)/4);
	return m + (l.second-l.first)/mag(l.second-l.first)*d; 
}

//angle of arc with radius r through p and q
ld angleA(point p, point q, ld r)	{
	return 2*asinl(norm(q-p)/(4*r*r));
}

//length of arc with radius r through p and q
ld lengthA(point p, point q, ld r) {
	return 2 * r * asinl(norm(q-p)/(4*r*r));
}

//circumcircle of 3 points as <center,radius>
pair<point,ld> circumcirclePPP(point a, point b, point c) {
	auto l = perpendicularS(a,b), m = perpendicularS(a,c);
	return make_pair(intersectLL(l.first,l.second,m.first,m.second), mag(p-a));
}

//incircle of 3 points as <center, radius>
pair<point,ld> incirclePPP(pt a, pt b, pt c){
	ld d = 1.0/(mag(a-b)+mag(a-c)+mag(b-c));
	return make_pair((a * mag(b-c) + b * mag(a-c) + c * mag(a-b))*d,cross(b-a,c-a)*d);
}

point rotateP(point p, ld t) { 
  return point(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}

//vector of all points line (a,b) intersects circle (c,r)
//errs on the side of accepting a single intersection
vector<point> intersectLC(point a, point b, point c, ld r) {
	vector<point> ans;
	point p = projectPL(c,a,b);
	ld d1 = mag(p-c), d2 = r*r - d1*d1, d = 1.0/mag(b-a);
	if(d2 < -EPS) return ans;
	if(d2 < EPS) {
		ans.push_back(p);
		return ans;
	}
	ans.push_back(p+(b-a)*d2*d);
	ans.push_back(p-(b-a)*d2*d);
	return ans;
}

// intersect circles with (center,radius) equal to (c,r) and (d,s)
vector<pt> intersectCC(point c, ld r, point d, ld s) {
	vector<point> ans;
	ld d1 = mag(c-d);
	if(d1 > r+s || d1+min(r,s) < max(r,s)) return ans;
	ld d2 = (d1*d1-r*r+s*s)/(2*d1);
	ld d3 = sqrtl(r*r-d2*d2);
	point v = (d-c)/d1;
	ans.push_back(c+v*d2 + rotate90CC(v)*d3);
	if(d3 > EPS) ans.push_back(c+v*d2 - rotate90CC(v)*d3);
	return ans;
}

// +------------------------------------------------+
// |                    POLYGONS                    |
// +------------------------------------------------+

//1 = Inside, 0 = On, -1 = Outside
int sidePG(point p, vector<point> &g) {
	int c = 0, n = g.size();
	for(int i = 0; i < n; i++)
    	if(onPS(p, g[i], g[(i+1) % n]))
      		return 0;
	for(int i = 0; i < n; i++){
		point a = g[i];
		point b = g[(i+1) % n];
		c ^= (a.y <= p.y != b.y <= p.y) && (b.y > a.y != (a.x - b.x)*(p.y - a.y) < (a.x - p.x)*(b.y - a.y));    
	}
	return c*2-1;
}

ld areaG(vector<point> &g) {
	ld area = 0;
	for(int i = 0; i < g.size(); i++)
		area += cross(g[i], g[(i+1)%g.size()]);
	return fabsl(area / 2.0);
}

// +------------------------------------------------+
// |              COMPARISON FUNCTIONS              |
// +------------------------------------------------+

//Sort around POINT assuming they all lie on the same halfplane
bool cmp1(point a, point b){
	return cross(a-POINT,b-POINT) > 0;
}

//Sort around POINT starting and ending from a line in the direction of DIR
bool cmp2(point a, point b){
	if(a==b) return false;
	point p = POINT, q = POINT+DIR;
	if(cross(a-p,a-q)*cross(b-p,b-q) >= 0){
		if(cross(a-p,a-q) == 0 && dot(a-p,a-q) > 0) return true;
		if(cross(b-p,b-q) == 0 && dot(b-p,b-q) > 0) return false;
		return cross(b-p,a-p) < 0;
	}
	return cross(a-p,a-q) > 0;
	       
}

//Sort according to projections on LN_A -> LN_B
bool cmp3(point a, point b){
	point p = projectPL(a, LN_A, LN_B), q = projectPL(b, LN_A, LN_B);
	return LN_A < LN_B != q < p;
}

//Sort lines by angle starting and ending from a line in the direction of LINE
bool cmp4(const ln &l, const ln &m){
	if(l==m) return false;
	pt p = LN_A, q = LN_B, a = LN_A + l.q - l.p, b = LN_A + m.q - m.p;
	if(cross(a-p, b-p) == 0 && (a<p == b<p))
		return sidePL(l.p, l.q, m.p) >= 0;
	if(cross(a-p,a-q) * cross(b-p,b-q) >= 0)
		return (cross(a-p,a-q) == 0 && dot(a-p,a-q) < 0) || (!(cross(b-p,b-q) == 0 && dot(b-p,b-q) < 0) && cross(b-p,a-p) < 0);
	return cross(a-p,a-q) > 0;
}


