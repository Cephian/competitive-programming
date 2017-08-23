namespace treap {
	typedef int data;
	struct node {
		data v;
		int p,sz=1;
		node *l=0, *r=0;
		node(data v):v(v),p(rand()) {};
		~node(){if(l) delete l; if(r) delete r; }
	};

	//node size
	int size(node *d) {
		return d?d->sz:0;
	}

	//reupdate from children
	void recalc(node *d) {
		d->sz = 1 + size(d->l) + size(d->r);
	}

	//split into nodes <= v and nodes > v
	void split(node *d, const data &v, node *&l, node *&r) {
		l = r = 0;
		if(!d) return;
		if(v <= d->v) {
			split(d->l,v,l,d->l);
			r = d;
		} else {
			split(d->r,v,d->r,r);
			l = d;
		}
		recalc(d);
	}

	//split such that l has size sz
	void split_size(node *d, int sz, node *&l, node *&r) {
		l = r = 0;
		if(!d) return;
		if(size(d->l) >= sz) {
			split_size(d->l,sz,l,d->l);
			r = d;
		} else {
			split_size(d->r,sz,d->r,r);
			l = d;
		}
		recalc(d);
	}

	//all values in l must be less than all those inof r
	node* merge(node *l, node *r) {
		if(!l || !r) return l?l:r;
		if(l->p < r->p) {
			l->r = merge(l->r,r);
			recalc(l);
			return l;
		}
		r->l = merge(l,r->l);
		recalc(r);
		return r;
	}

	//insert value v
	void insert(node *&d, data v) {
		node *l,*r;
		split(d,v,l,r);
		d = merge(merge(l,new node(v)),r);
	}

	//erase value v
	void erase(node *&d, data v) {
		node *l,*m,*r;
		split(d,v,l,m);
		split(m,v+1,m,r);
		if(m) delete m;
		d = merge(l,r);
	}
	 
	//value of element at 0-based index k
	data kth(const node* d, int k) {
		if(size(d->l) == k) return d->v;
		if(k < size(d->l)) return kth(d->l,k);
		return kth(d->r,k-size(d->l)-1);
	}
	 
	//number of elements strictly less than v
	int index(const node* d, const data &v) {
		if(!d) return 0;
		if(d->v == v) return size(d->l);
		if(v < d->v) return index(d->l,v);
		return 1 + size(d->l) + index(d->r,v);
	}

	//does d contain value v?
	bool contains(const node* d, const data &v) {
		if(!d) return false;
		if(v == d->v) return true;
		if(v < d->v) return contains(d->l,v);
		return contains(d->r,v);
	}
}

treap::node *root = 0;
