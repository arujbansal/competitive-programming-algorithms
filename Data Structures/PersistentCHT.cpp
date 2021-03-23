// CEOI 2009 Harbingers
// https://oj.uz/problem/view/CEOI09_harbingers

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <stack>
#include <queue>
#include <random>
#include <numeric>
#include <functional>
#include <chrono>
#include <utility>
#include <iomanip>
#include <assert.h>

using namespace std;

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define rng_init mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define rng_seed(x) mt19937 rng(x)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
#define int int64_t

const int MXN = 1e5 + 5, INF = 1e18;
vector<pair<int, int>> g[MXN];
int S[MXN], V[MXN], version[MXN], ans[MXN];
int last_version;

struct Line {
    int m, c;

    Line() {
        m = 0;
        c = INF;
    }

    Line(int m, int c) : m(m), c(c) {}

    int val(int x) { return m * x + c; }
};

struct Node {
    Line line;
    Node *lc, *rc;

    Node() : lc(0), rc(0) {}
};

deque<Node> buffer;
deque<Node*> root;

Node* new_node() {
    buffer.emplace_back();
    return &buffer.back();
}

void modify(Node* &prev, Node* &cur, int l, int r, Line new_line) {
    if (!prev) {
        cur->line = new_line;
        return;
    }

    cur->line = prev->line;

    if (r - l <= 0) return;

    cur->lc = prev->lc;
    cur->rc = prev->rc;

    int mid = l + (r - l) / 2;

    if (new_line.val(mid) < cur->line.val(mid))
        swap(cur->line, new_line);

    if (new_line.val(l) < cur->line.val(l)) {
        cur->lc = new_node();
        modify(prev->lc, cur->lc, l, mid, new_line);
    } else {
        cur->rc = new_node();
        modify(prev->rc, cur->rc, mid + 1, r, new_line);
    }
}

int query(Node* &cur, int l, int r, int x) {
    if (!cur) return INF;

    int res = cur->line.val(x);
    if (r - l <= 0) return res;

    int mid = l + (r - l) / 2;
    if (x <= mid) return min(res, query(cur->lc, l, mid, x));
    else return min(res, query(cur->rc, mid + 1, r, x));
}

void modify(int modify_version, int m, int c) {
    root.emplace_back(new_node());
    modify(root[modify_version], root[last_version], 0, 1000000000, Line(m, c));
}

int query(int qry_version, int x) {
    return query(root[qry_version], 0, 1000000000, x);
}

void dfs(int u, int p, int dist) {
    version[u] = ++last_version;

    ans[u] = min(dist * V[u] + S[u], query(version[p], V[u]) + dist * V[u] + S[u]);
    modify(version[p], -dist, ans[u]);

    for (const auto &[v, d] : g[u]) {
        if (v == p) continue;
        dfs(v, u, dist + d);
    }
}

void solve() {
    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int u, v, d;
        cin >> u >> v >> d;

        g[u].emplace_back(v, d);
        g[v].emplace_back(u, d);
    }

    for (int i = 2; i <= N; i++)
        cin >> S[i] >> V[i];

    root.emplace_back(new_node());
    buffer[0].line.c = 0;
    version[1] = 0;

    for (const auto &[v, d] : g[1]) {
        dfs(v, 1, d);
    }

    for (int i = 2; i <= N; i++)
        cout << ans[i] << " ";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    // cin >> TC;
    while (TC--) solve();
}
