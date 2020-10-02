/*
 *
 * USACO 2019 February Contest, Gold
 * Problem 1. Cow Land
 * Problem Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=921
 */
#include <bits/stdc++.h>

#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(nullptr)
#define setIO(i, o) freopen(i, "r", stdin), freopen(o, "w", stdout)
#define pb(x) push_back(x)
#define eb(x...) emplace_back(x)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
#define lc(i) 2*i
#define rc(i) 2*i+1
//#define int long long
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;

const int N = 1e5 + 5, MOD = 1e9 + 7, INF = 1e9 + 5;
vi g[N];
int a[N];

struct SegmentTree {
    int n;
    vector<int> a, t, lazy;

    void init(int x) {
        n = x;
        t.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void init(int x, vector<int> y) {
        n = x;
        a = y;
        t.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int merge(int x, int y) { return x ^ y; }

    int upd(int x, int y) { return x ^ y; }

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
        t[i] = upd(t[i], lazy[i]);
        if (l != r) {
            lazy[lc(i)] = upd(lazy[lc(i)], lazy[i]);
            lazy[rc(i)] = upd(lazy[rc(i)], lazy[i]);
        }
        lazy[i] = 0;
    }

    void modify(int i, int l, int r, int ql, int qr, int val) {
        if (l > qr || r < ql) return;
        if (lazy[i] != 0) push(i, l, r);
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
        if (l > qr || r < ql) return 0;
        if (lazy[i] != 0) push(i, l, r);
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
        for (const auto &v: g[u]) if (v != p) dfs(v, u);
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

signed main() {
    FAST_IO;
#ifdef arujbansal_local
    setIO("input.txt", "output.txt");
#endif
#ifndef arujbansal_local
    setIO("cowland.in", "cowland.out");
#endif

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    BinLiftLCA lca;
    lca.init(n);
    SegmentTree seg;
    seg.init(lca.timer);
    for (int i = 0; i < n; i++) seg.modify(lca.tin[i], lca.tout[i], a[i]);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, val;
            cin >> pos >> val;
            pos--;
            seg.modify(lca.tin[pos], lca.tout[pos], a[pos] ^ val);
            a[pos] = val;
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << (seg.query(lca.tin[u]) ^ seg.query(lca.tin[v]) ^ a[lca.query(u, v)]) << "\n";
        }
    }
}