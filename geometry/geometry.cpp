#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>
#include <stdlib.h>

using namespace std;

typedef long double ld;

ld INF = 1e100;
ld EPS = 1e-12;
ld PI = atanl(1)*4;

struct pt { 
	ld x, y; 
	pt(){}
	pt(ld x, ld y) : x(x), y(y) {}
	pt operator + (const pt &p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt &p) const { return pt(x-p.x, y-p.y); }
	pt operator * (ld c) const { return pt(x*c, y*c); }
	pt operator / (ld c) const { return pt(x/c, y/c); }
	bool operator == (const pt &p) const { return fabsl(x-p.x)+fabsl(y-p.y) < EPS; }
	bool operator < (const pt &p) const { return (x==p.x)?y<p.y:x<p.x; }
};

//Stores two points
//Allowed to be lines or points
#define p first
#define q second
typedef pair<pt,pt> ln;
typedef pair<pt,ld> circle;

pt POINT;
pt DIR;
pt LN_A, LN_B;

ld dot(pt p, pt q)     { return p.x*q.x+p.y*q.y; }
ld cross(pt p, pt q)   { return p.x*q.y-p.y*q.x; }
ld norm(pt p) {return p.x*p.x+p.y*p.y;}
ld mag(pt p)   { return sqrtl(p.x*p.x+p.y*p.y); }

//less than pi if aOb is clockwise 
ld angle(pt a, pt b){
	ld A = atan2l(cross(a,b),dot(a,b));
	if(A < 0) A += 2*PI;
	return A;
}

pt rotate90CC(pt p)   { return pt(-p.y,p.x); }
pt rotateP(pt p, ld t) { 
  return pt(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}
//rotates p around q by t
pt rotatePP(pt p, pt q, ld t) { 
  return rotateP(p-q, t) + q;
}

pt projectPL(pt p, pt a, pt b) {
  return a + (b-a)*dot(p-a, b-a)/norm(b-a);
}

pt projectPS(pt p, pt a, pt b) {
  if (a == b) return a;
  ld r = dot(p-a, b-a)/dot(a-b, a-b);
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}

pt reflectPL(pt p, pt a, pt b){
	return (a + (b-a)*dot(p-a, b-a)/norm(b-a))*2 - p;
}

bool onPL(pt p, pt a, pt b){
	return fabsl(cross(p-a, b-a)) < EPS;
}

bool onPS(pt p, pt a, pt b){
	return fabsl(cross(a-p, b-p)) < EPS && (a<p != b<p || p==a || p==b);
}

bool parallelLL(pt a, pt b, pt c, pt d) { 
  return fabsl(cross(b-a,d-c)) < EPS; 
}

bool equalLL(pt a, pt b, pt c, pt d) { 
  return onPL(c, a, b) && onPL(d, a, b) && onPL(a, c, d) && onPL(b, c, d);
}

//p -> a -> b: -1 = Clockwise, 0 = Colinear, 1 = Counterclockwise
//p with a->b: -1 = Right, 0 = On, 1 = Left 
// does direction PPP and side Point Halfplane
int sidePL(pt p, pt a, pt b) {
	ld d = cross(p-a,b-a);
	if(fabsl(d) < EPS) return 0;
	return (d<0)?-1:1;
}

bool intersectSS(pt a, pt b, pt c, pt d) {
  if(equalLL(a, b, c, d)){
  	if(b < a) swap(a, b);
  	if(d < c) swap(c, d);
  	if(c < a){
  		swap(a, c);
  		swap(b, d);
  	}
  	if(c==b || (c==d && c<b)) return true; //POINT
  	else if(c<b) return true; //SEGMENT
  	else return false; //NONE
  }
  else if (cross(a-d,a-c) * cross(b-d,b-c) <=0 && cross(c-b,c-a) * cross(d-b,d-a) <=0)
         return true; //POINT
  else return false; //NONE
}


pt intersectLL(pt a, pt b, pt c, pt d) {
  return a + (b-a)*(cross(c-a, c-d))/(cross(b-a, c-d));
}

//rotate around midpoint 90 degrees
ln perpendicularS(pt a, pt b) {
	ld m = (a.x + b.x + a.y + b.y)/2;
	return ln(pt(m-b.y, m-a.x), pt(m-a.y, m-b.x));
}

//return perpendicular to a->b going through p
ln perpendicularPL(pt p, pt a, pt b){
	return ln(p, a + (b-a)*dot(p-a, b-a)/norm(b-a));
}

pt centerA(pt a, pt b, ld r) {
	pt m = (a+b)/2;
	ln l = perpendicularS(a,b);
	ld d = sqrt(r*r - norm(b-a)/4);
	return m + (l.q-l.p)/mag(l.q-l.p)*d; 
}
ld angleA(pt a, pt b, ld r)	{return 2*asinl(norm(b-a)/(4*r*r));}
ld arclenA(pt a, pt b, ld r)     {return 2*r*asinl(norm(b-a)/(4*r*r));}
ld areaA(pt a, pt b, ld r)		 { return r*r*asinl(norm(b-a)/(4*r*r));}

circle circumcirclePPP(pt a, pt b, pt c) {
	ln l=perpendicularS(a,b),m=perpendicularS(a,c);
	pt p = intersectLL(l.p,l.q,m.p,m.q);
	ld r = mag(p-a);
	return circle(p, r);
}

circle incirclePPP(pt a, pt b, pt c){
	ld d = 1.0/(mag(a-b)+mag(a-c)+mag(b-c));
	pt p = (a*mag(b-c) + b*mag(a-c) + c*mag(a-b))*d;
	ld r = cross(b-a,c-a)*d;
	return circle(p,r);
}

bool onPG(pt p, vector<pt> &g) {
  for (int i = 0; i < g.size(); i++)
    if (onPS(p, g[i], g[(i+1)%g.size()]))
      return true;
  return false;
}

//1 = Inside, 0 = On, -1 = Outside
int sidePG(pt p, vector<pt> &g) {
	for (int i = 0; i < g.size(); i++)
    	if (onPS(p, g[i], g[(i+1)%g.size()]))
      		return 0;
	int c = 0;
	for (int i = 0; i < g.size(); i++){
		pt a = g[i];
		pt b = g[(i+1)%g.size()];
		c ^= (a.y <= p.y != b.y <= p.y) && (b.y > a.y != (a.x - b.x)*(p.y - a.y) < (a.x - p.x)*(b.y - a.y));    
	}
	return c*2-1;
}



bool intersectSL(pt a, pt b, pt c, pt d){
	return cross(a-c,a-d) * cross(b-c,b-d) <=0;
}


vector<pt> intersectLC(pt a, pt b, pt c, ld r) {
	vector<pt> ans;
	pt p = projectPL(c,a,b);
	ld d1 = mag(p-c);
	ld d2 = r*r - d1*d1;
	if(d2 < -EPS) return ans;
	if(d2 < EPS) {
		ans.push_back(p);
		return ans;
	}
	ans.push_back(p+(b-a)*d2/mag(b-a));
	ans.push_back(p-(b-a)*d2/mag(b-a));
	return ans;
}

// intersect circles with center/radii c/r and d/s
vector<pt> intersectCC(pt c, ld r, pt d, ld s) {
	vector<pt> ans;
	ld d1 = mag(c-d);
	if(d1 > r+s || d1+min(r, s) < max(r, s)) return ans;
	ld d2 = (d1*d1-r*r+s*s)/(2*d1);
	ld d3 = sqrtl(r*r-d2*d2);
	pt v = (d-c)/d1;
	ans.push_back(c+v*d2 + rotate90CC(v)*d3);
	if(d3 > EPS)
		ans.push_back(c+v*d2 - rotate90CC(v)*d3);
	return ans;
}

ld areaG(vector<pt> &g) {
	ld area = 0;
	for(int i = 0; i < g.size(); i++)
		area += cross(g[i], g[(i+1)%g.size()]);
	return area / 2.0;
}

pt centroidG(vector<pt> &g) {
	pt c(0,0);
	for (int i = 0; i < g.size(); i++){
		int j = (i+1)%g.size();
		c = c + (g[i]+g[j])*cross(g[i], g[j]);
	}
	return c / (6.0 * areaG(g));
}

vector<pt> intersectLG(pt a, pt b, vector<pt> &g){
	vector<pt> ans;
	for (int i = 0; i < g.size(); i++) {
		int j = (i+1)%g.size();
		if(intersectSL(g[i],g[j],a,b))
			ans.push_back(intersectLL(g[i],g[j],a,b));
	}
	return ans;
}

vector<pt> intersectSG(pt a, pt b, vector<pt> &g){
	vector<pt> ans;
	for (int i = 0; i < g.size(); i++) {
		int j = (i+1)%g.size();
		if(intersectSS(g[i],g[j],a,b))
			ans.push_back(intersectLL(g[i],g[j],a,b));
	}
	return ans;
}

//Sort around POINT assuming they all lie on the same halfplane
bool cmp1(pt a, pt b){
	return cross(a-POINT,b-POINT) > 0;
}

//Sort around POINT starting and ending from a line in the direction of LINE
bool cmp2(pt a, pt b){
	if(a==b) return false;
	pt p = POINT;
	pt q = POINT+DIR;
	if(cross(a-p,a-q)*cross(b-p,b-q) >= 0){
		if(cross(a-p,a-q) == 0 && dot(a-p,a-q) > 0) return true;
		if(cross(b-p,b-q) == 0 && dot(b-p,b-q) > 0) return false;
		return cross(b-p,a-p) < 0;
	}
	return cross(a-p,a-q) > 0;
	       
}

//Sort according to projections on LN_A -> LN_B
bool cmp3(pt a, pt b){
	pt p = projectPL(a, LN_A, LN_B);
	pt q = projectPL(b, LN_A, LN_B);
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

//Helper functions for intersecting halfplanes
bool away(ln a, ln b){
	return !cross(a.p-a.q, b.p-b.q) && ((a.q<a.p) != (b.q<b.p)) && sidePL(a.q, a.p, b.p) >= 0;
}

bool exclude(ln a, ln b, ln c){
	return (away(a, b) || away(b, c) || away(a, c)) || 
		  (cross(a.p-a.q,b.p-b.q)*cross(b.p-b.q,c.p-c.q) > 0 && cross(a.p-a.q,b.p-b.q)*cross(c.p-c.q,a.p-a.q) > 0 && 
		  sidePL(intersectLL(a.p, a.q, c.p, c.q), b.q, b.p) >= 0);
}

bool covering(ln a, ln b, ln c){
	return exclude(a, ln(b.q, b.p), c);
}

vector<pt> intersectionH(vector<ln> v){
	set<ln, bool(*)(const ln&, const ln&)> s(&cmp4);
	set<ln> q;
	vector<pt> pts;
	for(auto u : v){
		s.insert(u);
		q.insert(u);	
	}
	while(q.size() && s.size()>2){
		ln l = *q.begin();
		q.erase(l);
		auto i = s.find(l);
		auto j = i;
		if(++i==s.end()) i = s.begin();
		if(j==s.begin()) j = s.end();
		if(exclude(*(--j), l, *i)) return pts; //empty intersection
		if(covering(*j, l, *i)) {
			q.insert(*j);
			q.insert(*i);
			s.erase(l);
		}
	}
	for (auto i = s.begin(); i != s.end(); ++i){
		ln a = *i;
		auto j = i;
		if(++j==s.end()) j = s.begin();
		ln b = *j;
		if(cross(a.q-a.p, b.q-b.p) < 0){
			//infinite intersection
		}
		pts.push_back(intersectLL(a.p, a.q, b.p, b.q));
	}
	return pts;
}

vector<pt> intersectionGG(vector<pt> &g, vector<pt> &h){
	vector<ln> v;
	for(int i=0; i<g.size(); i++)
		v.push_back(ln(g[i], g[(i+1)%g.size()]));
	for(int i=0; i<h.size(); i++)
		v.push_back(ln(h[i], h[(i+1)%h.size()]));
	return intersectionH(v);
}

int main() {
	
	
	
	
	return 0;
}
