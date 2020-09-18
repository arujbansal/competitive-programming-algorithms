/*
 * USACO 2019 December Contest, Gold
 * Problem 2. Milk Visits
 * Problem Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=970
 */

#include <bits/stdc++.h>

#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(nullptr)
#define setIO(i, o) freopen(i, "r", stdin), freopen(o, "w", stdout)
#define trav(e, x) for (auto &(e) : (x))
#define pb(x) push_back(x)
#define eb(x...) emplace_back(x)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
#define lc(i) 2*i
#define rc(i) 2*i+1
//#define int long long
using namespace std;
using ii = pair<int, int>;
using vi = vector<int>;

const int N = 1e5 + 5, MOD = 1e9 + 7, INF = 1e9 + 5;
int n, q, l;
vi g[N], st[N];
int c[N], depth[N], tin[N], tout[N], par[N][21];
bool ans[N];
int timer;

struct query {
    int v, milk, idx;
};

vector<query> queries[N];

void dfs(int u = 0, int p = -1, int dep = 0) {
    tin[u] = timer++;
    depth[u] = dep;
    par[u][0] = (p == -1 ? 0 : p);
    for (int j = 1; j <= l; j++) par[u][j] = par[par[u][j - 1]][j - 1];
    trav(v, g[u]) if (v != p) dfs(v, u, dep + 1);
    tout[u] = timer - 1;
}

bool isAnc(int x, int v) {
    return tin[x] <= tin[v] && tout[x] >= tout[v];
}

int findLCA(int u, int v) {
    if (isAnc(u, v)) return u;
    if (isAnc(v, u)) return v;
    for (int j = l; j >= 0; j--) if (!isAnc(par[u][j], v)) u = par[u][j];
    return par[u][0];
}

bool valid(int x, int u, int v) {
    return depth[x] >= depth[u] && depth[x] <= depth[v];
}

void dfs2(int u = 0, int p = -1) {
    st[c[u]].pb(u);
    trav(qry, queries[u]) {
        int v = qry.v, req = qry.milk, idx = qry.idx;
        int lca = findLCA(u, v);
        if (st[req].empty()) continue;
        int last = st[req].back();
        if (valid(last, lca, u)) ans[idx] = true;
    }
    trav(v, g[u]) if (v != p) dfs2(v, u);
    st[c[u]].pop_back();
}

signed main() {
    FAST_IO;
    setIO("milkvisits.in", "milkvisits.out");

    cin >> n >> q;
    l = ceil(log2(n));
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        c[i]--;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    for (int i = 0; i < q; i++) {
        int u, v, milk;
        cin >> u >> v >> milk;
        u--, v--, milk--;
        queries[u].eb(query{v, milk, i});
        queries[v].eb(query{u, milk, i});
    }
    dfs();
    dfs2();
    for (int i = 0; i < q; i++) cout << ans[i];
}
