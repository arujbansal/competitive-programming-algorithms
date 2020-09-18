struct SparseTable {
    int n, k;
    vector<int> lg;
    vector<vector<int>> st;

    void init(int x, const vector<int> &a) {
        n = x;
        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        k = lg[n];
        st.assign(n + 1, vi(k + 1, INF));
        build(a);
    }

    int merge(int x, int y) { return min(x, y); }

    void build(const vector<int> &x) {
        for (int i = 0; i < n; i++) st[i][0] = x[i];
        for (int j = 1; j <= k; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        int j = lg[r - l + 1];
        return merge(st[l][j], st[r - (1 << j) + 1][j]);
    }
};