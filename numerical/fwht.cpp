/* matrices for bit operations and their inverses (fast-walsh-hadamard)
# XOR #
    |1  1|             |1  1|
T = |1 -1| and 2T^-1 = |1 -1|
note: there is a scale factor of 2
FORWARD TRANSFORM: a=a+b,b=a-2*b;
REVERSE TRANSFORM: same as first

# OR #
    |1  1|            |0  1|
T = |1  0| and T^-1 = |1 -1|
FORWARD TRANSFORM: a=a+b, b=a-b;
REVERSE TRANSFORM: b=a-b, a=a-b;


# AND #
    |0  1|            |-1 1|
T = |1  1| and T^-1 = |1  0|
FORWARD TRANSFORM: b=a+b, a=b-a;
REVERSE TRANSFORM: a=b-a, b=b-a;
*/


// fast walsh-hadamard-like transform
// n should be a power of 2
void FWHT(ll* d, int n) {
	for(int g = 1; g*2 <= n; g *= 2)
		for(int i = 0; i < n; i += 2*g)
			for(int j = i; j < i+g; ++j) {
				ll &a = d[j], &b = d[j+g];
				//PASTE RELEVANT LINE HERE
			}
}


const int N = 8;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//find P^77 under XOR tranform
	ll h[N] = {0,1,2,3,4,5,6,7};
	FWHT(h,N);
	for(int i = 0; i < N; ++i) h[i] = pw(h[8],77);
	FWHT(h,N); //needs seperate inverse if not xor
	for(int i = 0; i < N; ++i) h[i] /= N //only need if xor, might need mod arith

	return 0;
}