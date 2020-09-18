struct UFDS {
    int n;
    vector<int> par, rank;

    void init(int x) {
        n = x;
        par.resize(x);
        rank.assign(n, 0);
        iota(all(par), 0);
    }

    int getPar(int x) {
        if (par[x] == x) return x;
        else return par[x] = getPar(par[x]);
    }

    bool unite(int x, int y) {
        x = getPar(x);
        y = getPar(y);
        if (x == y) return false;
        if (rank[x] > rank[y]) swap(x, y);
        par[y] = x;
        if (rank[x] == rank[y]) rank[y]++;
        return true;
    }
};