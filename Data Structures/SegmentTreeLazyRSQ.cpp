struct SegmentTree {
    int n;
    vector<int> a, t, lazy;

    void init(int x, vector<int> &y) {
        n = x;
        a = move(y);
        t.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int merge(int x, int y) { return x + y; }

    int upd(int x, int y) { return x + y; }

    void build(int i, int l, int r) {
        if (l == r) {
            t[i] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(lc(i), l, mid);
        build(rc(i), mid + 1, r);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    void push(int i, int l, int r) {
        if (lazy[i] != 0) {
            t[i] = upd(t[i], lazy[i] * (r - l + 1));
            if (l != r) {
                lazy[lc(i)] = upd(lazy[rc(i)], lazy[i]);
                lazy[rc(i)] = upd(lazy[lc(i)], lazy[i]);
            }
            lazy[i] = 0;
        }
    }

    void modify(int i, int l, int r, int ql, int qr, int val) {
        push(i, l, r);
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            lazy[i] = upd(lazy[i], val);
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        modify(lc(i), l, mid, ql, qr, val);
        modify(rc(i), mid + 1, r, ql, qr, val);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    int query(int i, int l, int r, int ql, int qr) {
        push(i, l, r);
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return t[i];
        int mid = (l + r) / 2;
        int resL = query(lc(i), l, mid, ql, qr);
        int resR = query(rc(i), mid + 1, r, ql, qr);
        return merge(resL, resR);
    }

    void modify(int l, int r, int val) { modify(1, 0, n - 1, l, r, val); }

    void modify(int pos, int val) { modify(1, 0, n - 1, pos, pos, val); }

    int query(int l, int r) { return query(1, 0, n - 1, l, r); }

    int query(int pos) { return query(1, 0, n - 1, pos, pos); }
};