template<class Modifier>
struct segment_tree : public Modifier {
    /*
        Modifier Requires:
        1. typename T : Data type used throughout the tree.
        2. T identity : Return element/base value.
        3. bool range_each : tree[i] * range length?
        4. T merge : Merging two segment tree nodes.
        5. T update : Process for updating nodes.
    */

    using T = typename Modifier::T;

    int n;
    vector<T> a, tree, lazy;
    T identity = Modifier::identity;

    segment_tree(int _n = 0) { init(_n); }

    segment_tree(int _n, const vector<T> &_a) { init(_n, _a); }

    void init(int _n) {
        n = _n;
        tree.assign(4 * n, identity);
        lazy.assign(4 * n, identity);
    }

    void init(int _n, const vector<T> &_a) {
        n = _n;
        tree.resize(4 * n);
        lazy.resize(4 * n);

        a = _a;
        build(1, 0, n - 1);
    }

    void build(int i, int l, int r) {
        lazy[i] = identity;

        if (l == r) {
            tree[i] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(2 * i, l, mid);
        build(2 * i + 1, mid + 1, r);

        tree[i] = Modifier::merge(tree[2 * i], tree[2 * i  + 1]);
    }

    void propagate(int i, int l, int r) {
        if (lazy[i] == identity) return;

        tree[i] = Modifier::update(tree[i], lazy[i] * (Modifier::range_each ? (r - l + 1) : 1));

        if (l != r) {
            lazy[2 * i] = Modifier::update(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = Modifier::update(lazy[2 * i + 1], lazy[i]);
        }

        lazy[i] = identity;
    }

    void modify(int i, int l, int r, int ql, int qr, T val) {
        propagate(i, l, r);
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            lazy[i] = Modifier::update(lazy[i], val);
            propagate(i, l, r);
            return;
        }

        int mid = (l + r) / 2;

        modify(2 * i, l, mid, ql, qr, val);
        modify(2 * i + 1, mid + 1, r, ql, qr, val);

        tree[i] = Modifier::merge(tree[2 * i], tree[2 * i + 1]);
    }

    T query(int i, int l, int r, int ql, int qr) {
        propagate(i, l, r);
        if (l > qr || r < ql) return identity;
        if (l >= ql && r <= qr) return tree[i];

        int mid = (l + r) / 2;
        return Modifier::merge(query(2 * i, l, mid, ql, qr), query(2 * i + 1, mid + 1, r, ql, qr));
    }

    void modify(int l, int r, T val) { modify(1, 0, n - 1, l, r, val); }

    T query(int l, int r) { return query(1, 0, n - 1, l, r); }

    T query(int pos) { return query(1, 0, n - 1, pos, pos); }
};

// struct RARM {
//     using T = int;

//     const T identity = numeric_limits<T>::min();
//     bool range_each = false;

//     T merge(const T &x, const T &y) { return max(x, y); }

//     T update(const T &x, const T &y) { return x + y; }
// };