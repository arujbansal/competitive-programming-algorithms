template<typename T>
struct segment_tree {
    int n;
    vector<T> tree;
    T identity_element;
    function<T(const T&, const T&)> merge;

    segment_tree(int _n, T _identity_element, const function<T(const T&, const T&)> &_merge) { 
        init(_n, _identity_element, _merge); 
    }

    void init(int _n, T _identity_element, const function<T(const T&, const T&)> &_merge) {
        n = _n;
        identity_element = _identity_element;
        merge = _merge;
        tree.assign(2 * n, identity_element);
    }

    void build(const vector<T> &a) {
        for (int i = 0; i < n; i++)
            tree[i + n] = a[i];

        for (int i = n - 1; i > 0; i--)
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    void identity_modify(int pos, T val) {
        pos += n;

        for (tree[pos] = merge(tree[pos], val); pos >>= 1; )
            tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
    }

    void increment(int pos, T val) {
        pos += n;

        for (tree[pos] += val; pos >>= 1; )
            tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
    }

    void set(int pos, T val) {
        pos += n;

        for (tree[pos] = val; pos >>= 1; )
            tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
    }

    T query(int l, int r) {
        T res = identity_element;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, tree[l++]);
            if (!(r & 1)) res = merge(res, tree[r--]);
        }

        return res;
    }

    T query(int pos) { return query(pos, pos); }
};