#include <bits/stdc++.h>
using namespace std;

const int N = 3e5+5,INF = 0x7fffffff;
int n,l,r;

struct node {
	int p,v,sz=1,lz=0;
	node *l=0, *r=0;
	node(int v):v(v),p((rand()<<16)^16) {};
	~node(){delete l; delete r; }
};

void push(node* d) {
	if(d->l) d->l->lz += d->lz;
	if(d->r) d->r->lz += d->lz;
	d->v += d->lz;
	d->lz = 0;
}

int rbst_size(node *d) { return (d)?d->sz:0; }

void rbst_update(node *d) {
	d->sz = 1+rbst_size(d->l)+rbst_size(d->r);
}

// l will contain elements w/ values [-INF, v)
// r wil contain elements w/ value >= v
void rbst_split(node *d, int v, node *&l, node *&r) {
	l = r = 0;
	if(!d) return;
	push(d);
	if(v <= d->v) {
		rbst_split(d->l,v,l,d->l);
		r=d;
	} else {
		rbst_split(d->r,v,d->r,r);
		l=d;
	}
	rbst_update(d);
}

node* rbst_merge(node *l, node *r) {
	if(!l || !r) return l?l:r;
	push(l); push(r);
	if(l->p < r->p) {
		l->r = rbst_merge(l->r,r);
		rbst_update(l);
		return l;
	}
	r->l = rbst_merge(l,r->l);
	rbst_update(r);
	return r;
}

bool rbst_contains(node* d, int v) {
	if(!d) return false;
	push(d);
	if(v == d->v) return true;
	if(v < d->v) return rbst_contains(d->l,v);
	return rbst_contains(d->r,v);
}

void rbst_insert(node *&d, int v) {
	if(rbst_contains(d,v)) return;
	node *l,*r;
	rbst_split(d,v,l,r);
	d = rbst_merge(rbst_merge(l,new node(v)),r);
}

// erase node with value v
void rbst_erase(node *&d, int v) {
	node *l,*m,*r;
	rbst_split(d,v,l,m);
	rbst_split(m,v+1,m,r);
	if(m) delete m;
	d = rbst_merge(l,r);
}

//value of element at index k
int rbst_at(node* d, int k) {
	if(rbst_size(d->l) == k) return d->v;
	if(k < rbst_size(d->l)) return rbst_at(d->l,k);
	return rbst_at(d->r,k-rbst_size(d->l)-1);
}

//number of elements smaller than v
int rbst_index(node* d, int v) {
	if(!d) return 0;
	if(d->v == v) return rbst_size(d->l);
	if(v < d->v) return rbst_index(d->l,v);
	return 1+rbst_size(d->l)+rbst_index(d->r,v);
}

node* root;

int main() {
	rbst_insert(root,2);
	rbst_insert(root,3);
	rbst_insert(root,5);
	rbst_insert(root,9);
	//tree is 2 3 5 9
	node *a,*b;
	rbst_split(root,a,b,4);
	b->lz += 1; //adjust lazy value
	root = rbst_merge(a,b);
	//tree is 2 3 6 10
	return 0;
}