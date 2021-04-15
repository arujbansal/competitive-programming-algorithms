#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template<typename T>
struct fenwick_tree {
    int n;
    vector<T> tree;

    fenwick_tree() {}

    fenwick_tree(int _n) { init(_n); }

    void init(int _n) {
        n = _n;
        tree.assign(n + 1, 0);
    }

    void build(const vector<T> &a) {
        for (int i = 1; i <= n; i++) {
            int j = i + (i & -i);

            tree[i] += a[i - 1];
            if (j <= n) tree[j] += tree[i];
        }
    }

    void increment(int pos, T val) {
        for (int i = pos + 1; i <= n; i += i & -i)
            tree[i] += val;
    }

    T query(int pos) {
        T res = 0;

        for (int i = pos + 1; i > 0; i -= i & -i)
            res += tree[i];

        return res;
    }

    T query(int l, int r) { return query(r) - query(l - 1); }
};

const int MXN = 3e5 + 5;
const long long INF = 1e15;
int N, M, K;
vector<int> stations[MXN];
int meteors_req[MXN], ans[MXN];
int showers[MXN][3];
fenwick_tree<long long> meteors;

void update(int l, int r, long long delta) {
    if (r < l) {
        update(0, r, delta);
        r = M - 1;
    }

    meteors.increment(l, delta);
    meteors.increment(r + 1, -delta);
}

void parallel_binary_search(int l, int r, const vector<int> &queries) {
    if (l > r || queries.empty()) return;

    int mid = (l + r) / 2;

    for (int i = l; i <= mid; i++)
        update(showers[i][0], showers[i][1], showers[i][2]);

    vector<int> new_queries[2];

    for (const auto &state : queries) {
        long long gathered = 0;

        for (const auto &station : stations[state]) {
            gathered += meteors.query(station);
            if (gathered >= 1e18) break;
        }

        if (gathered >= meteors_req[state]) {
            ans[state] = min(ans[state], mid);
            new_queries[0].push_back(state);
        } else new_queries[1].push_back(state);
    }

    parallel_binary_search(mid + 1, r, new_queries[1]);

    for (int i = l; i <= mid; i++)
        update(showers[i][0], showers[i][1], -showers[i][2]);

    parallel_binary_search(l, mid - 1, new_queries[0]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int x;
        cin >> x;
        x--;

        stations[x].push_back(i);
    }

    for (int i = 0; i < N; i++)
        cin >> meteors_req[i];

    cin >> K;

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < 3; j++)
            cin >> showers[i][j];

        for (int j = 0; j < 2; j++)
            showers[i][j]--;
    }

    meteors.init(MXN);

    vector<int> queries(N);
    iota(queries.begin(), queries.end(), 0);

    for (int i = 0; i < N; i++)
        ans[i] = 1e9;

    parallel_binary_search(0, K - 1, queries);

    for (int i = 0; i < N; i++) {
        if (ans[i] < 1e9) cout << ans[i] + 1 << "\n";
        else cout << "NIE\n";
    }
}