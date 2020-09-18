/*
 * USACO 2019 December Contest, Gold
 * Problem 1. Milk Pumping
 * Problem Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=969
 */

#include <bits/stdc++.h>

#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(nullptr)
#define setIO(i, o) freopen(i, "r", stdin), freopen(o, "w", stdout)
#define trav(e, x) for (auto &e : x)
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

const int MAXN = 1e3 + 5, INF = 1e9 + 5, MOD = 1e9 + 7;
int n, m;

struct edge {
    int u, v, c, f;
};

vector<edge> edges;
vector<ii> adj[MAXN];
vi dist;

int dijkstra(int flow) {
    for (int i = 0; i < n; i++) adj[i].clear();
    dist.assign(n, INF);
    for (auto e: edges) {
        if (e.f >= flow) {
            adj[e.u].eb(e.v, e.c);
            adj[e.v].eb(e.u, e.c);
        }
    }
    dist[0] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        ii cur = pq.top();
        pq.pop();
        int u = cur.second, curC = cur.first;
        if (dist[u] != curC) continue;
        trav(e, adj[u]) {
            int v = e.first;
            int cost = e.second;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.emplace(dist[v], v);
            }
        }
    }
    return (dist[n - 1] < INF ? dist[n - 1] : -1);
}

signed main() {
    FAST_IO;
    setIO("pump.in", "pump.out");

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c, f;
        cin >> u >> v >> c >> f;
        u--, v--;
        edges.eb(edge{u, v, c, f});
    }
    double res = 0;
    for (int i = 1; i <= 1000; i++) {
        int shortest = dijkstra(i);
        if (shortest > -1) res = max(res, (double) i / shortest);
    }
    cout << (int) (res * 1000000);
}
