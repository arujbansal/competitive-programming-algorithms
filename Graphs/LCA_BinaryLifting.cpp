struct BinLiftLCA {
    int n, k, timer;
    vi tin, tout;
    vector<vector<int>> par;

    void init(int x) {
        n = x;
        k = ceil(log2(n));
        timer = 0;
        tin.resize(n);
        tout.resize(n);
        par.assign(n, vector<int>(k + 1, 0));
        dfs();
    }

    void dfs(int u = 0, int p = -1) {
        tin[u] = timer++;
        par[u][0] = (p == -1 ? 0 : p);
        for (int j = 1; j <= k; j++) par[u][j] = par[par[u][j - 1]][j - 1];
        trav(v, g[u]) if (v != p) dfs(v, u);
        tout[u] = timer - 1;
    }

    bool isAnc(int x, int v) {
        return tin[x] <= tin[v] && tout[x] >= tout[v];
    }

    int query(int u, int v) {
        if (isAnc(u, v)) return u;
        if (isAnc(v, u)) return v;
        for (int j = k; j >= 0; j--) if (!isAnc(par[u][j], v)) u = par[u][j];
        return par[u][0];
    }
};