#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct point { 
	ll x, y; 
	point(){}
	point(ll x, ll y) : x(x), y(y) {}
	point operator + (const point &p) const { return point(x+p.x, y+p.y); }
	point operator - (const point &p) const { return point(x-p.x, y-p.y); }
};

ll dot(point p, point q) { return p.x*q.x + p.y*q.y; }
ll cross(point p, point q) { return p.x*q.y - p.y*q.x; }
ll norm(point p) { return p.x*p.x + p.y*p.y; }
double mag(point p) { return sqrt(p.x*p.x + p.y*p.y); }

bool intersectSL(point a, point b, point c, point d){
	double x = cross(a-c,a-d), y = cross(b-c,b-d);
	return x == 0 || y == 0 || (x<0) != (y<0);
}

int sidePL(point p, point a, point b) {
	ll d = cross(p-a,b-a);
	if(d == 0) return 0;
	return (d<0)?-1:1;
}

double intersect_scale(point a, point b, point c, point d) {
	return cross(a-c, a-b)/(double)cross(d-c, a-b);
}

double project_scale(point p, point a, point b) {
	return dot(p-a, b-a) / (double)norm(b-a);
}

point p[200];
int n;

double test(int i, int j) {
	point A = p[i], B = p[j];
	vector<double> hits;
	for(int x = 0; x < n; ++x) {
		int y = (x+1)%n, w = (x-1+n)%n, z = (y+1)%n;
		if(!intersectSL(p[x],p[y],A,B)) continue;
		bool X = sidePL(p[x],A,B)==0, Y = sidePL(p[y],A,B)==0;
		if(!X && !Y)
			hits.push_back(intersect_scale(p[x],p[y],A,B));
		else if(X && Y) {
			int opp = (dot(p[y]-p[x],B-A)<0)?1:-1;
			if(sidePL(p[w],A,B) == opp)
				hits.push_back(project_scale(p[x],A,B));
			if(sidePL(p[z],A,B) == opp)
				hits.push_back(project_scale(p[y],A,B));
		}
		if(sidePL(p[x],A,B)==0 && sidePL(p[w],A,B) == -sidePL(p[y],A,B))
			hits.push_back(project_scale(p[x],A,B));
	}
	double ans = 0;
	sort(hits.begin(),hits.end());
	for(int i = 1; i < hits.size(); i += 2)
		ans = max(ans,hits[i]-hits[i-1]);
	return ans * mag(B-A);
}

int main() {	
	scanf("%d",&n);
	for(int i = 0; i < n; ++i)
		scanf("%lld%lld",&p[i].x,&p[i].y);
	double ans = 0;
	for(int i = 0; i < n; ++i)
		for(int j = i+1; j < n; ++j)
			ans = max(ans, test(i,j));
	printf("%.12lf\n",ans);
}