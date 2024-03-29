template<typename T>
struct segment_tree {
    int n;
    vector<T> a, tree;
    T identity;
    function<T(const T&, const T&)> merge;

    segment_tree() {}

    segment_tree(int _n, T _identity, const function<T(const T&, const T&)> &_merge) {
        init(_n, _identity, _merge);
    }

    void init(int _n, T _identity, const function<T(const T&, const T&)> &_merge) {
        n = _n;
        identity = _identity;
        merge = _merge;

        tree.assign(4 * n, identity);
    }

    void build(int i, int l, int r) {
        if (l == r) {
            tree[i] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(2 * i, l, mid);
        build(2 * i + 1, mid + 1, r);

        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    void identity_modify(int i, int l, int r, int pos, T val) {
        if (l == r) {
            tree[i] = merge(tree[i], val);
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= mid) identity_modify(2 * i, l, mid, pos, val);
        else identity_modify(2 * i + 1, mid + 1, r, pos, val);

        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    void increment(int i, int l, int r, int pos, T val) {
        if (l == r) {
            tree[i] += val;
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= mid) increment(2 * i, l, mid, pos, val);
        else increment(2 * i + 1, mid + 1, r, pos, val);

        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    T query(int i, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return identity;
        if (l >= ql && r <= qr) return tree[i];

        int mid = (l + r) / 2;
        T resL = query(2 * i, l, mid, ql, qr);
        T resR = query(2 * i + 1, mid + 1, r, ql, qr);

        return merge(resL, resR);
    }

    void build(const vector<T> &_a) {
        a = _a;
        build(1, 0, n - 1);
    }

    void identity_modify(int pos, T val) { identity_modify(1, 0, n - 1, pos, val); }

    void increment(int pos, T val) { increment(1, 0, n - 1, pos, val); }

    T query(int pos) { return query(1, 0, n - 1, pos, pos); }

    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};