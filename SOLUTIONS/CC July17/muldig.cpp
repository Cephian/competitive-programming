#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
 
int p;
 
vector<tuple<int,int,int> > U;
 
void mlt(int x, int y, int z) {
	int o = 4000;
	U.eb(0,y,o);
	U.eb(x,0,o+1);
	for(int i = 2; i <= p-1; ++i)
		U.eb(o+1,0,o+1);
	U.eb(o+1,o,z);
}
 
//puts 1 in z if tape[y]==val
void cf(int y, int val, int z) {
	int o = 3000;
	U.eb(y,0,o);
	val = (val+1)%p;
	while(val != 0) {
		U.eb(o,0,o);
		val = (val+1)%p;
	}
	U.eb(0,0,o+1);
	for(int i = 1; i <= p-1; ++i)
		mlt(o,o+1,o+1);
	U.eb(0,o+1,z);
}
 
int _add[7][7];
int _dva[7][7];
int _dvm[7][7];
 
 
void func(int x, int y, int z, int f[7][7]) {
	int o = 2000, O = 2100,Oo=2200;
	for(int u = 0; u < p; ++u) {
		cf(x,u,o+u);
		cf(y,u,O+u);
	}
	U.eb(0,0,Oo);
	for(int u = 0; u < p; ++u) {
		for(int v = 0; v < p; ++v) {
			mlt(o+u,O+v,Oo+1);
			int a = f[u][v];
			if(a==0) a = 1;
			else if(a==1) a = 0;
			mlt(Oo+1,a,Oo+1);
			U.eb(0,Oo+1,Oo+1);
			mlt(Oo,Oo+1,Oo);
		}
	}
	U.eb(0,Oo,z);
	U.eb(0,z,z);
}
 
void add(int x, int y, int z) {func(x,y,z,_add);}
void dva(int x, int y, int z) {func(x,y,z,_dva);}
void dvm(int x, int y, int z) {func(x,y,z,_dvm);}
 
int pr() {
	printf("%d\n",(int)U.size());
	for(const auto &p : U)
		printf("%d %d %d\n",get<0>(p),get<1>(p),get<2>(p));
	return 0;
}
 
int main() {
	scanf("%d",&p);
	for(int i = 0; i < p; ++i) {
		for(int j = 0; j < p; ++j) {
			int k = j;
			if(k==0) k=1;
			else if(k==1) k = 0;
			printf("%d ",(i+1)*k%p);
			_add[i][j] = (i+j)%p;
			_dva[i][j] = (i+j)/p;
			_dvm[i][j] = (i*j)/p;
		}
		printf("\n");
	}
	
	int X1=p, X2=p+1, Y1=p+2, Y2=p+3;
	int A=p+4, B=p+5, C=p+6, D=p+7;
 
	int t = 1000;
 
	//X1,Y1
	mlt(X1,Y1,B);
	dvm(X1,Y1,A);
 
	//X1,Y2
	mlt(X1,Y2,C);
	dvm(X1,Y2,t);
	dva(t,B,t+1);
	add(A,t+1,A);
	add(t,B,B);
 
	//X2,Y1
	mlt(X2,Y1,t);
	dvm(X2,Y1,t+1);
	dva(t+1,B,t+2);
	add(t+2,A,A);
	add(t+1,B,B);
	dva(t,C,t+1);
	dva(t+1,B,t+2);
	add(t+2,A,A);
	add(t+1,B,B);
	add(t,C,C);
 
	//X2,Y2
	mlt(X2,Y2,D);
	dvm(X2,Y2,t);
	dva(t,C,t+1);
	dva(t+1,B,t+2);
	add(t+2,A,A);
	add(t+1,B,B);
	add(t,C,C);
 
	return pr();
} 