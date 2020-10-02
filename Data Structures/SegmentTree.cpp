struct SegmentTree {
    int n;
    vector<int> a, t;

    void init(int x) {
        n = x;
        t.assign(4 * n, 0);
    }

    void init(int x, vector<int> y) {
        n = x;
        a = move(y);
        t.resize(4 * n);
        build(1, 0, n - 1);
    }

    int merge(int x, int y) { return x + y; }

    int upd(int x, int y) { return y; }

    void build(int i, int l, int r) {
        if (l == r) {
            t[i] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc(i), l, mid);
        build(rc(i), mid + 1, r);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    void modify(int i, int l, int r, int pos, int val) {
        if (l == r) {
            t[i] = upd(t[i], val);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) modify(lc(i), l, mid, pos, val);
        else modify(rc(i), mid + 1, r, pos, val);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    int query(int i, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return t[i];
        int mid = (l + r) >> 1;
        return merge(query(lc(i), l, mid, ql, qr), query(rc(i), mid + 1, r, ql, qr));
    }

    void modify(int pos, int val) { modify(1, 0, n - 1, pos, val); }

    int query(int l, int r) { return query(1, 0, n - 1, l, r); }
};