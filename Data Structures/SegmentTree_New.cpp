template<typename T>
struct segment_tree {
    int n;
    vector<T> a, t;

    const T returnElement = 0;

    segment_tree(int n, T val) {
        this->n = n;
        t.assign(4 * n, val);
    }

    segment_tree(vector<T> &a) {
        this->a = a;
        n = int(a.size());
        t.resize(4 * n);

        build(1, 0, n - 1);
    }

    void assign(int n, T val) {
        this->n = n;
        t.assign(4 * n, val);
    }

    void assign(vector<T> &a) {
        this->a = a;
        n = int(a.size());
        t.resize(4 * n);

        build(1, 0, n - 1);
    }

    T merge(const T &x, const T &y) {
        return x + y;
    }

    void upd(T &x, const T &y) {
        x += y;
    }

    void build(int i, int l, int r) {
        if (l == r) {
            t[i] = a[l];
            return;
        }

        int mid = (l + r) >> 1;

        build(2 * i, l, mid);
        build(2 * i + 1, mid + 1, r);

        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }

    void modify(int i, int l, int r, int pos, T val) {
        if (l == r) {
            upd(t[i], val);
            return;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid) modify(2 * i, l, mid, pos, val);
        else modify(2 * i + 1, mid + 1, r, pos, val);

        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }

    T query(int i, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return returnElement;
        if (l >= ql && r <= qr) return t[i];

        int mid = (l + r) >> 1;

        T resL = query(2 * i, l, mid, ql, qr);
        T resR = query(2 * i + 1, mid + 1, r, ql, qr);

        return merge(resL, resR);
    }

    void modify(int pos, T val) { modify(1, 0, n - 1, pos, val); }

    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};