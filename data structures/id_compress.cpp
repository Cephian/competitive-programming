//compress arbitrary objects with sequential ids
template <class T>
struct id_compress {
	map<T,int> m;
	vector<T> o;
	inline int id(const T &val) {
		const auto it = m.find(val);
		if(it == m.end()) {
			o.push_back(val);
			return m[val] = m.size();
		}
		return it->second;
	}

	inline T original(int i) {
		return o[i];
	}
};
