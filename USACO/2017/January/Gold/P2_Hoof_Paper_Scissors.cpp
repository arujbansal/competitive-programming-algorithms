/*
 * USACO 2017 January Contest, Gold
 * Problem 2. Hoof, Paper, Scissors
 */

#include <bits/stdc++.h>

#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(nullptr)
#define setIO(i, o) freopen(i, "r", stdin), freopen(o, "w", stdout)
#define trav(e, x) for (auto &e : x)
#define pb(x) push_back(x)
#define eb(x...) emplace_back(x)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
//#define int long long
using namespace std;
using vi = vector<int>;
using ii = pair<int, int>;

vector<int> moves;

bool beats(int x, int y) {
    if (x == 0 && y == 1) return true;
    if (x == 1 && y == 2) return true;
    if (x == 2 && y == 0) return true;
    return false;
}

// dp(i, j, k) : i - considering first i moves, j - gesture changes left, k - current gesture
int dp[100005][25][3];

int f(int i, int j, int k) {
    if (i == 0) return (j < 0 ? 0 : beats(moves[i], k));
    if (dp[i][j][k] > -1) return dp[i][j][k];
    int ans = f(i - 1, j, k);
    for (int x = 0; x < 3; x++) {
        if (x == k) continue;
        if (j > 0) ans = max(ans, f(i - 1, j - 1, x));
    }
    return dp[i][j][k] = beats(moves[i], k) + ans;
}


signed main() {
    FAST_IO;
    setIO("hps.in", "hps.out");

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        int y;
        if (x == 'H') y = 0;
        else if (x == 'P') y = 1;
        else y = 2;
        moves.pb(y);
    }
    memset(dp, -1, sizeof dp);
    cout << max({f(n - 1, k, 0), f(n - 1, k, 1), f(n - 1, k, 2)});
}
