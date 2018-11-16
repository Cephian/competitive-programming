#include <bits/stdc++.h>
using namespace std;


typedef long double ld;
constexpr ld EPS = 1e-10;
struct point { 
	ld x, y, z; 
	point(){}
	point(ld x, ld y, ld z) : x(x), y(y), z(z){}
	point operator + (const point &p) const { return point(x+p.x, y+p.y, z+p.z); }
	point operator - (const point &p) const { return point(x-p.x, y-p.y, z-p.z); }
	point operator * (ld c) const { return point(x*c, y*c, z*c); }
	point operator / (ld c) const { return point(x/c, y/c, z/c); }
	bool operator == (const point &p) const { return fabsl(x-p.x) + fabsl(y-p.y) + fabsl(z-p.z) < EPS; }
	bool operator < (const point &p) const { return (x==p.x) ? ((y==p.y) ? z < p.z : y < p.y) : x < p.x; }
};

point cross(point p, point q) {return point(p.y * q.z - q.y * p.z, p.z * q.x - q.z * p.x, p.x * q.y - q.x * p.y);}
ld dot(point p, point q) { return p.x*q.x + p.y*q.y + p.z*q.z; }
ld norm(point p) { return p.x*p.x + p.y*p.y + p.z*p.z; }
ld mag(point p) { return sqrtl(p.x*p.x + p.y*p.y + p.z*p.z); }
ld dist(point p, point q) { return mag(p - q); }
ld sq_dist(point p, point q) { return norm(p - q); }

// distance from point (x, y, z) to plane aX + bY + cZ + d = 0
ld DistPtPl(point p, ld a, ld b, ld c, ld d) {
	return abs(a*p.x + b*p.y + c*p.z + d) / sqrt(a*a + b*b + c*c);
}

// distance between parallel planes aX + bY + cZ + d1 = 0 and
// aX + bY + cZ + d2 = 0
ld DistPlPl(double a, double b, double c, double d1, double d2) {
	return abs(d1 - d2) / sqrt(a*a + b*b + c*c);
}

// distance from point p to line x y

ld DistPtLn(point p, point x, point y) {
	double pd2 = norm(x-y);
	point z;
	if (pd2 == 0) {
		z = x;
	} else {
		double u = dot(p-x, y-x) / pd2;
		z = x + (y-x) * u;
	}
	return mag(z-p);
}

// distance from point p to segment x y
ld DistPtSg(point p, point x, point y) {
	double pd2 = norm(x-y);
	point z;
	if (pd2 == 0) {
		z = x;
	} else {
		double u = dot(p-x, y-x) / pd2;
		z = x + (y-x) * u;
		if (u < 0) {
			z = x;
	 	}
	 	if (u > 1.0) {
	 		z = y;
	 	}
	}
	return mag(z-p);
}

//Volume of the tetrahedron defined by these three points an the origin
ld Volume(point a, point b, point c){
	return dot(a, cross(b, c))/6;
}

int main(){
	while(true){
		ld a, b, c, d, e, f, g, h, i;
		cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;
		cout << Volume(point(a, b, c), point(d, e, f), point(g, h, i));
	}
}


