#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

//SPECIAL GNU
__gcd(a, b) //GCD : do not use let a or b be 0
__builtin_popcount(a) //number of 1 bits
__builtin_clz(a) // count leading zeroes
inline int log2(int a) { return 31-__builtin_clz(a); } //floor(log(a))

//ORDER STATISTIC TREE
typedef tree<int, null_type, less<int>,
	rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set X;
X.insert(1);
cout << *X.find_by_order(0) << endl;
cout << X.order_of_key(1) << endl;

//ROPE
rope <int> v; //use as usual STL container
int n, m;
cin >> n >> m;
for(int i = 1; i <= n; ++i)
	v.push_back(i); //initialization
int l, r;
for(int i = 0; i < m; ++i) {
	cin >> l >> r;
	--l, --r;
	rope <int> cur = v.substr(l, r - l + 1);
	v.erase(l, r - l + 1);
        v.insert(v.mutable_begin(), cur);
}
for(rope <int>::iterator it = v.mutable_begin(); it != v.mutable_end(); ++it)
	cout << *it << " ";

//REGEX
regex r("^[^f]*$");

string result = regex_replace(string start, regex match, string replace);
// regex_match matches the whole string, whereas regex_search checks to see if it matches a substring

