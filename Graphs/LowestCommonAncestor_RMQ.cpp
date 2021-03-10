struct LCA {
    int n, m, k;
    vector<vector<int>> adj, sparse_table;
    vector<int> euler, first_occurrence;
    int timer;
    bool lca_built;

    LCA(int _n = 0) { 
        lca_built = false;

        if (_n > 0)
            init(_n);
    }

    void init(int _n) {
        lca_built = false;

        n = _n;

        adj.resize(n);
        for (int i = 0; i < n; i++)
            adj[i].clear();

        euler.clear();
        first_occurrence.resize(n);
        timer = 0;
    }

    void add_edge(int u, int v) {
        assert(n > 0);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void run(int root = 0) {
        assert(n > 0);

        dfs(root, -1);
        build();

        lca_built = true;
    }

    void dfs(int u = 0, int p = -1) {
        first_occurrence[u] = timer++;
        euler.push_back(u);

        for (const auto &v : adj[u]) {
            if (v == p) continue;
            
            dfs(v, u);
            euler.push_back(u);
            timer++;
        }
    }

    void build() {
        k = 31 - __builtin_clz(timer) + 1;

        sparse_table.resize(k);

        for (int i = 0; i < k; i++)
            sparse_table[i].resize(timer - (1 << i) + 2);

        for (int j = 0; j < timer; j++)
            sparse_table[0][j] = euler[j];

        for (int i = 1; i < k; i++) {
            for (int j = 0; j + (1 << i) - 1 < timer; j++) {
                int x = sparse_table[i - 1][j];
                int y = sparse_table[i - 1][j + (1 << (i - 1))];

                sparse_table[i][j] = (first_occurrence[x] < first_occurrence[y] ? x : y);
            }
        }
    }

    int query(int u, int v) {
        assert(lca_built == true);

        int l = first_occurrence[u], r = first_occurrence[v];
        if (l > r)
            swap(l, r);

        int i = 31 - __builtin_clz(r - l + 1);

        int x = sparse_table[i][l], y = sparse_table[i][r - (1 << i) + 1];
        return first_occurrence[x] < first_occurrence[y] ? x : y;
    }
};