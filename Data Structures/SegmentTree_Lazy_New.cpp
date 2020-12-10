template<typename T>
struct SegmentTree {
    int n;
    vector<T> a, t, lazy;

    void init(vector<T> &a) {
        this->a = a;
        n = (int) a.size();

        t.resize(4 * n);
        lazy.assign(4 * n, 0);

        build(1, 0, n - 1);
    }

    void init(int n) {
        this->n = n;
        t.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    T merge(const T &x, const T &y) { return x + y; }

    void upd(T &x, const T &y) { x += y; }

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

    void push(int i, int l, int r) {
        if (lazy[i] == 0) return;

        upd(t[i], lazy[i] * (r - l + 1));

        if (l != r) {
            upd(lazy[2 * i], lazy[i]);
            upd(lazy[2 * i + 1], lazy[i]);
        }

        lazy[i] = 0;
    }

    void modify(int i, int l, int r, int ql, int qr, T val) {
        if (l > qr || r < ql) return;

        if (l >= ql && r <= qr) {
            upd(lazy[i], val);
            push(i, l, r);
            return;
        }

        push(i, l, r);

        int mid = (l + r) >> 1;

        modify(2 * i, l, mid, ql, qr, val);
        modify(2 * i + 1, mid + 1, r, ql, qr, val);

        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }

    T query(int i, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        push(i, l, r);
        if (l >= ql && r <= qr) return t[i];

        int mid = (l + r) >> 1;

        T resL = query(2 * i, l, mid, ql, qr);
        T resR = query(2 * i + 1, mid + 1, r, ql, qr);

        return merge(resL, resR);
    }

    void modify(int pos, T val) { modify(1, 0, n - 1, pos, pos, val); }

    void modify(int l, int r, T val) { modify(1, 0, n - 1, l, r, val); }

    T query(int pos) { return query(1, 0, n - 1, pos, pos); }

    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};