/*
 * USACO 2020 January Contest, Gold
 * Problem 1. Time is Mooney
 * Problem Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=993
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
#define int long long
using namespace std;
using ii = pair<int, int>;
using vi = vector<int>;

const int N = 1e3 + 1, MOD = 1e9 + 7, INF = 1e9 + 5;

signed main() {
    FAST_IO;
    setIO("time.in", "time.out");

    int n, m, c;
    cin >> n >> m >> c;
    int money[n];
    for (int i = 0; i < n; i++) cin >> money[i];
    vector<ii> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges.eb(u, v);
    }
    int dp[n][N];
    for (int i = 0; i < n; i++) for (int j = 0; j < N; j++) dp[i][j] = -1;
    dp[0][0] = 0;
    for (int j = 1; j < N; j++) {
        for (auto edge : edges) {
            int u = edge.first, v = edge.second;
            if (dp[u][j - 1] < 0) continue;
            dp[v][j] = max(dp[v][j], dp[u][j - 1] + money[v]);
        }
    }
    int ans = 0;
    for (int j = 0; j < N; j++) ans = max(ans, dp[0][j] - c * j * j);
    cout << ans;
}
