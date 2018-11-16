// store polynomials in a,b. set LA = len(a) and L = len(b)
// call calculate(), a now stores a*b.
const int maxn=4000000;
const int g=3,bigp=479*(1<<21)+1,x=21;
int LA,LB;
int a[maxn]={0},b[maxn]={0},w[maxn];
int C,N,L;
int powc(int a,int b) {
	if (!b) return 1;
	int d = powc(a,b/2);
	d = ll(d)*d%bigp;
	if(b%2) d = ll(d)*a%bigp;
	return d;
}
//K is the length of x[]
//v=0 : DFT, v=1 : IDFT
void FFT(int x[],int K,int v){
	w[0] = 1;
	int G = powc(g,(bigp-1)/K);
	for(int i = 0; i < K; ++i)
		w[i+1] = (ll)w[i]*G%bigp;
	for(int i=0,j=0; i<K; ++i) {
		if(i>j) swap(x[i],x[j]);
		for(int l=K>>1; (j^=l)<l; l>>=1);
	}
	for(int i = 2; i <= K; i<<=1)
		for(int j = 0; j < K; j += i)
			for(int l = 0; l < i>>1; l++) {
				int t = (ll)x[j+l+(i>>1)]*w[v?K-(K/i)*l:(K/i)*l]%bigp;
				x[j+l+(i>>1)] = ((ll)x[j+l]-t+bigp)%bigp;
				x[j+l] += t;
				x[j+l] %= bigp;
      		}
	if(v) {
		int r = powc(N,bigp-2);
		for(int i = 0; i < N; ++i)
			a[i] = ll(a[i])*r%bigp;
	}
}
void calculate() {
	//LA,LB are length of a[] and b[] (include a[0] and b[0])
	N=1,C=LA+LB,L=0;
	while (N<=C) N*=2,++L;
	for(int i=LA; i<N; i++) a[i] = 0;
	for(int i=LB; i<N; i++) b[i] = 0;
	FFT(a,N,0);FFT(b,N,0);
	for (int i=0; i<N; i++)
		a[i]=(ll)a[i]*b[i]%bigp;
	FFT(a,N,1);
}
