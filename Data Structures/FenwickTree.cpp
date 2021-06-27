template<typename T>
struct fenwick_tree {
    int n;
    vector<T> tree;

    fenwick_tree(int _n = 0) { init(_n); }

    void init(int _n) {
        n = _n;
        tree.assign(n + 1, 0);
    }

    void build(const vector<T> &a) {
        for (int i = 1; i <= n; i++) {
            int j = i + (i & -i);

            tree[i] += a[i - 1];
            if (j <= n) tree[j] += tree[i];
        }
    }

    void increment(int pos, T val) {
        for (int i = pos + 1; i <= n; i += i & -i)
            tree[i] += val;
    }

    T query(int pos) {
        T res = 0;

        for (int i = pos + 1; i > 0; i -= i & -i)
            res += tree[i];

        return res;
    }

    T query(int l, int r) { return query(r) - query(l - 1); }
};