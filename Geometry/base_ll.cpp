#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point { 
	ll x, y; 
	point(){}
	point(ll x, ll y) : x(x), y(y) {}
	point operator + (const point &p) const { return point(x+p.x, y+p.y); }
	point operator - (const point &p) const { return point(x-p.x, y-p.y); }
	point operator * (ll c) const { return point(x*c, y*c); }
	bool operator == (const point &p) const { return x == p.x && y == p.y; }
	bool operator < (const point &p) const { return (x==p.x) ? y<p.y : x<p.x; }
};

ostream& operator<<(ostream &o, const point &p) {
	return o << "(" << p.x << "," << p.y << ")",o;
}

ll dot(point p, point q) { return p.x*q.x + p.y*q.y; }
ll cross(point p, point q) { return p.x*q.y - p.y*q.x; }
ll norm(point p) { return p.x*p.x + p.y*p.y; }
double mag(point p) { return sqrt(p.x*p.x + p.y*p.y); }
ll sq_dist(point p, point q) { return norm(p-q); }

// +------------------------------------------------+
// |               LINES AND SEGMENTS               |
// +------------------------------------------------+

//how far along (a,b) is p? (projected)
//0 at a, 1 at b
double project_scale(point p, point a, point b) {
	return dot(p-a, b-a) / (double)norm(b-a);
}

//how far along (a,b) is p? (projected)
// 0 -> at a, |b-a| -> at b 
double project_dist(point p, point a, point b) {
	return dot(p-a, b-a) / (double)mag(b-a);
}

// where do lines (a,b) and (c,d) intersect?
// result T means c + (d-c)*T
double intersect_scale(point a, point b, point c, point d) {
	return cross(a-c, a-b)/(double)cross(d-c, a-b);
}

//is p on line (a,b) ?
bool onPL(point p, point a, point b){
	return cross(p-a, b-a) == 0;
}

//is p on segment (a,b) ?
bool onPS(point p, point a, point b){
	return cross(a-p, b-p) == 0 && ((a<p) != (b<p) || p==a || p==b);
}

// are lines (a,b) and (c,d) parallel?
bool parallelLL(point a, point b, point c, point d) { 
  return cross(b-a,d-c) == 0; 
}

// are lines (a,b) and (c,d) equal?
bool equalLL(point a, point b, point c, point d) { 
  return onPL(c,a,b) && onPL(d,a,b) && onPL(a,c,d) && onPL(b,c,d);
}

//p -> a -> b: -1 = Clockwise, 0 = Colinear, 1 = Counterclockwise
//p with a->b: -1 = Left, 0 = On, 1 = Right 
int sidePL(point p, point a, point b) {
	ll d = cross(p-a,b-a);
	if(d == 0) return 0;
	return (d<0)?-1:1;
}

//does segment (a,b) intersect line (c,d) ?
bool intersectSL(point a, point b, point c, point d){
	ll x = cross(a-c,a-d), y = cross(b-c,b-d);
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

point rotate90CC(point p) {
	return point(-p.y,p.x);
}

// +------------------------------------------------+
// |                CIRCLES AND ARCS                |
// +------------------------------------------------+

//angle of arc with radius r through p and q
double angleA(point p, point q, double r)	{
	return 2 * asin(norm(q-p)/(4*r*r));
}

//length of arc with radius r through p and q
double lengthA(point p, point q, double r) {
	return 2 * r * asin(norm(q-p)/(4*r*r));
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
		c ^= ((a.y<=p.y) != (b.y<=p.y)) && ((b.y>a.y) != ((a.x-b.x)*(p.y-a.y)<(a.x-p.x)*(b.y-a.y)));    
	}
	return c*2-1;
}

//note it is always half an integer
double areaG(vector<point> &g) {
	ll area = 0;
	for(int i = 0; i < (int)g.size(); i++)
		area += cross(g[i], g[(i+1)%g.size()]);
	return fabs(area / 2.0);
}

// +------------------------------------------------+
// |              COMPARISON FUNCTIONS              |
// +------------------------------------------------+

// "globals" we might need to capture
point POINT, DIR, LN_A, LN_B;

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

//Sort lines by angle starting and ending from a line in the direction of LINE
struct ln {
	point p, q;
	bool operator==(const ln& l) const { return p==l.p && q==l.q; }
};
bool cmp4(const ln &l, const ln &m){
	if(l==m) return false;
	point p = LN_A, q = LN_B, a = LN_A + l.q - l.p, b = LN_A + m.q - m.p;
	if(cross(a-p, b-p) == 0 && ((a<p) == (b<p)))
		return sidePL(l.p, l.q, m.p) >= 0;
	if(cross(a-p,a-q) * cross(b-p,b-q) >= 0)
		return (cross(a-p,a-q) == 0 && dot(a-p,a-q) < 0) || (!(cross(b-p,b-q) == 0 && dot(b-p,b-q) < 0) && cross(b-p,a-p) < 0);
	return cross(a-p,a-q) > 0;
}

int main() {
	
}

