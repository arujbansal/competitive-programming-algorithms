struct SparseTable {
    int n, k;
    vector<int> a;
    vector<vector<int>> st;

    void init(int x, vector<int> y) {
        n = x;
        k = lg(n);
        a = y;
        st.assign(n + 1, vector<int>(k + 1));
        build();
    }

    int lg(int x) { return 31 - __builtin_clz(x); }

    int merge(int x, int y) { return a[x] < a[y] ? x : y; }

    void build() {
        for (int i = 0; i < n; i++) st[i][0] = i;
        for (int j = 1; j <= k; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        int j = lg(r - l + 1);
        return a[merge(st[l][j], st[r - (1 << j) + 1][j])];
    }
};