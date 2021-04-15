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
int meteors_req[MXN], ans[MXN], showers[MXN][3], L[MXN], R[MXN];
fenwick_tree<long long> meteors;

void update(int l, int r, long long delta) {
    if (r < l) {
        update(0, r, delta);
        r = M - 1;
    }

    meteors.increment(l, delta);
    meteors.increment(r + 1, -delta);
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

    for (int i = 0; i < N; i++) {
        ans[i] = 1e9;
        L[i] = 0, R[i] = K - 1;
    }

    while (true) {
        vector<int> queries[K];

        bool all_answered = true;

        for (int i = 0; i < N; i++) {
            if (L[i] > R[i]) continue;

            all_answered = false;
            queries[(L[i] + R[i]) / 2].push_back(i);
        }

        if (all_answered) break;

        meteors.init(M + 5);

        for (int mid = 0; mid < K; mid++) {
            update(showers[mid][0], showers[mid][1], showers[mid][2]);

            for (const auto &state : queries[mid]) {
                long long gathered = 0;

                for (const auto &station : stations[state]) {
                    gathered += meteors.query(station);
                    if (gathered >= 1e18) break;
                }

                if (gathered >= meteors_req[state]) {
                    ans[state] = min(ans[state], mid);
                    R[state] = mid - 1;
                } else L[state] = mid + 1;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (ans[i] < 1e9) cout << ans[i] + 1 << "\n";
        else cout << "NIE\n";
    }
}