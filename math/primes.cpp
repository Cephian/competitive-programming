//UNTESTED
bool miller_rabin_primality(ll N) {
	// deterministic for all <= 2 ^ 64
	static const int p[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
	if (N <= 1) return false;
	for (int i = 0; i < 12; ++i) {
		if (p[i] == N) return true;
		if (N % p[i] == 0) return false;
	}
	ll c = N - 1, g = 0;
	while (!(c & 1)) c >>= 1, ++g;
	for (int i = 0; i < 12; ++i) {
		ll k = modpow(p[i], c, N);
		for (int j = 0; j < g; ++j) {
			ll kk = modmul(k, k, N);
			if (kk == 1 && k != 1 && k != N - 1) return false;
			k = kk;
		}
		if (k != 1) return false;
	}
	return true;
}

//UNTESTED
mt19937 gen(time(0));
ll pollard_rho(ll N) {
	if (N % 2 == 0) return 2;
	ll xx = uniform_int_distribution<ll>()(gen) % N, x = xx;
	ll c = uniform_int_distribution<ll>()(gen) % N, d = 1;
	for (int iters = 0; iters < 2000; ++iters) {
		x = (modmul(x, x, N) + c) % N;
		xx = (modmul(xx, xx, N) + c) % N;
		xx = (modmul(xx, xx, N) + c) % N;
		d = __gcd(abs(x - xx), N);
		if (d != 1 && d != N) break;
	}
	return d;
}

//factorize integers in [0,N)
int fact[N];
void factor_all() {
	for(int i = 1; i < N; ++i)
		fact[i] = i;
	for(int i = 2; i < N; ++i)
		if(fact[i] == i)
			for(ll j = ll(i)*i; j < N; j += i)
				fact[j] = i;
}

//factored list of integers
map<int,int> factor(int n) {
	map<int,int> a;
	while(n != 1) {
		++a[fact[n]];
		n/=fact[n];
	}
	return a;
}

//return unsorted list of divisors given factorization
//topologically ordered by poset digraph
vector<int> divisors(map<int,int>& f) {
	int m = 1;
	for(auto p : f)
		m *= p.second+1;
	vector<int> ans;
	for(--m; m>=0; --m) {
		int w=m,a=1;
		for(auto p : f) {
			int e = w%(p.second+1);
			w/=p.second+1;
			while(e--)
				a*=p.first;
		}
		ans.push_back(a);
	}
	return ans;
}