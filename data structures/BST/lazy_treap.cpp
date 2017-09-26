namespace treap {
	typedef int data;
	struct node {
		data v, lazy=0;
		int p,sz=1;
		node *l=0, *r=0;
		node(data v):v(v),p(rand()) {};
		~node(){if(l) delete l; if(r) delete r; }
	};

	//lazy update to all values in subtree of d
	inline void update(node* d, data val) {
		if(d) d->lazy += val;
	}

	//push lazy value of d to children
	inline void push(node *d) {
		if(d && d->lazy) {
			if(d->l) d->l->lazy += d->lazy;
			if(d->r) d->r->lazy += d->lazy;
			d->v += d->lazy;
			d->lazy = 0;
		}
	}

	//node size
	inline int size(node *d) {
		return d?d->sz:0;
	}

	//recalc size from children
	inline void recalc(node *d) {
		d->sz = 1 + size(d->l) + size(d->r);
	}

	//split into nodes <= v and nodes > v
	void split(node *d, data v, node *&l, node *&r) {
		l = r = 0;
		if(!d) return;
		push(d);
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
		push(d);
		if(size(d->l) >= sz) {
			split(d->l,sz,l,d->l);
			r = d;
		} else {
			split(d->r,sz,d->r,r);
			l = d;
		}
		recalc(d);
	}

	//all values in l must be less than all those in r
	node* merge(node *l, node *r) {
		if(!l || !r) return l?l:r;
		push(l), push(r);
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
	void insert(node *&d, int v) {
		node *l,*r;
		split(d,v,l,r);
		node* q = new node(v);
		d = merge(merge(l,q),r);
	}

	//erase value v
	void erase(node *&d, int v) {
		node *l,*m,*r;
		split(d,v,l,m);
		split(m,v+1,m,r);
		if(m) delete m;
		d = merge(l,r);
	}
	 
	//value of element at 0-based index k
	data kth(node* d, int k) {
		push(d);
		if(size(d->l) == k) return d->v;
		if(k < size(d->l)) return kth(d->l,k);
		return kth(d->r,k-size(d->l)-1);
	}
	 
	//number of elements strictly less than v
	int index(node* d, data v) {
		if(!d) return 0;
		push(d);
		if(v == d->v) return size(d->l);
		if(v < d->v) return index(d->l,v);
		return 1 + size(d->l) + index(d->r,v);
	}

	//does d contain value v?
	bool contains(node* d, data v) {
		if(!d) return false;
		push(d);
		if(v == d->v) return true;
		if(v < d->v) return contains(d->l,v);
		return contains(d->r,v);
	}

	void print(node* d) {
		if(!d) return;
		print(d->r);
		printf("%d ",d->sol);
		print(d->l);
	}
}

treap::node *root = 0;