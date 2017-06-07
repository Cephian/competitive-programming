//modified from an example solution of an NAIPC 2017 problem "Apple Market"

#define EPS (1e-8)
#define sign(x) (((x)>EPS)-((x)<(-EPS)))
#define T ld
struct vec {
	T x,y,z;    //coordinates/data
	vec(T x, T y, T z=0.):x(x),y(y),z(z){}
	vec() {x=y=z=0;}
  
	// vector ops
	vec& operator=(const vec& b) { x=b.x; y=b.y; z=b.z; return *this; }
	vec operator+(const vec& b) const { return vec(x+b.x, y+b.y, z+b.z); }
	vec operator-(const vec& b) const { return vec(x-b.x, y-b.y, z-b.z); }
	T operator*(const vec& b) const { return x*b.x + y*b.y + z*b.z; }
	vec operator^(const vec& b) const { return vec(y*b.z - z*b.y,z*b.x - x*b.z,x*b.y - y*b.x); }
	// scalar mult
	vec operator*(T k) const { return vec(x*k,y*k,z*k); }
	vec operator/(T k) const { return vec(x/k,y/k,z/k); }
	vec operator-() const { return vec(-x,-y,-z); }  // negation
  
	T sqlen() const { return (*this) * (*this); }

	bool operator<(const vec& v) const {
		if (x != v.x) return x < v.x;
		if (y != v.y) return y < v.y;
		return z < v.z;
	}
};
vec operator*(T k, vec v) { return v*k; }
#undef T

#define INSIDE (-1)
#define ON (0)
#define OUTSIDE (1)

typedef vector<vector<vec> > hull;

bool eq(ld a, ld b) {
	return abs(b-a) <= EPS;
}

ld len(const vec& a) {
	return sqrtl(a.sqlen());
}

int side(vec& a, vec& b, vec& c, vec& x) {
	vec norm = (b-a) ^ (c-a);
	vec me = x-a;
	return sign(me * norm);
}

bool is_colinear(vec& a, vec& b, vec& c) {
	vec w = (b-a)^(c-a);
	return eq(w.sqlen(),0);
}

vec projection(vec& a, vec& b, vec& c, vec& x) {
	if (side(a,b,c,x) == ON) return x;
	vec norm = (b-a) ^ (c-a);
	vec ans = x - norm * ((norm * (x-a)) / (norm * norm));
	return ans;
}

struct ph {
    size_t operator()(const pii& k) const {
    	return k.first*123456789 ^ k.second*21212121;
    }
};

hull find_hull(vec* P, int N) {
	random_shuffle(P, P+N);

	// Find 4 non-degenerate points (make a tetrahedron)
	for(int j = 2; j < N; ++j)
		if(!is_colinear(P[0],P[1],P[j])) {
			swap(P[j], P[2]);
			break; 
		}
	for(int j = 3; j < N; ++j)
		if (side(P[0],P[1],P[2],P[j]) != 0) {
			swap(P[j], P[3]);
			break;
		}

	// Canonicalize them
	if (side(P[0],P[1],P[2],P[3]) == OUTSIDE)
		swap(P[0], P[1]);

	vector< vector<int> > H {{0,1,2},{0,3,1},{0,2,3},{3,2,1}},H2;
	// incrementally add points
	unordered_map<pii, int, ph> D;
	for (auto & f : H)
		for(int i = 0; i < 3; ++i)
			++D[pii(f[i],f[(i+1)%3])];
	for(int j = 4; j < N; ++j) {
		H2.clear();
		H2.reserve(H.size());
		for (auto & f : H) {
			int s = side(P[f[0]],P[f[1]],P[f[2]],P[j]);
			if (s == INSIDE || s == ON) {
				H2.push_back(f);
			} else {
				for(int i = 0; i < 3; ++i)
					--D[pii(f[i],f[(i+1)%3])];
			}
		}

		const auto tmp = H2;
		for(auto & f : tmp) {
			for(int i = 0; i < 3; ++i) {
				int a = f[i],b=f[(i+1)%3];
				if (D[pii(a,b)] + D[pii(b,a)]==1) {
					// add a new face
					H2.push_back({a, j, b});
					++D[pii(a,j)];
					++D[pii(j,b)];
					++D[pii(b,a)];
				}
			}
		}
		swap(H,H2);
	}
	hull C;
	for(auto v : H)
		C.push_back({P[v[0]], P[v[1]], P[v[2]]});
	return C;
}

vec p[1001];

int main() {
	int n,T;
	cin >> T;
	cout << setprecision(10) << fixed;
	while(T--) {
		cin >> n;
		for(int i = 0; i < n; ++i)
			cin >> p[i].x >> p[i].y >> p[i].z;
		hull h = find_hull(p,n);
		ld surface = 0, volume = 0;
		for(auto t : h) {
			surface += len((t[1]-t[0])^(t[2]-t[0]))/2.0;
			volume += abs(((t[1]-p[0])^(t[0]-p[0]))*(t[2]-p[0]))/6.0;
		}
		cout << surface << " " << volume << "\n";
	}
}