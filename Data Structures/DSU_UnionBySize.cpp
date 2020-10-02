struct DSU {
    int n;
    vector<int> par, s;

    void init(int x) {
        n = x;
        par.resize(n);
        iota(all(par), 0);
        s.assign(n, 1);
    }

    int get(int x) {
        if (par[x] == x) return x;
        return par[x] = get(par[x]);
    }

    bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (s[x] < s[y]) swap(x, y);
        s[x] += s[y];
        par[y] = x;
        return true;
    }

    int getSz(int x) {
        x = get(x);
        return s[x];
    }
};