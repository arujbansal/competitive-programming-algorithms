#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MXN = 3e5 + 5;
int N, K;
int A[MXN];
pair<int, int> tree[4 * MXN];

pair<int, int> merge(const pair<int, int> &x, const pair<int, int> &y) {
    if (x.first == y.first)
        return make_pair(x.first, x.second + y.second);

    if (x.second > y.second)
        return make_pair(x.first, x.second - y.second);

    return make_pair(y.first, y.second - x.second);
}

void build(int i, int l, int r) {
    if (l == r) {
        tree[i] = make_pair(A[l], 1);
        return;
    }

    int mid = (l + r) / 2;

    build(2 * i, l, mid);
    build(2 * i + 1, mid + 1, r);

    tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
}

pair<int, int> query(int i, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return make_pair(-1, 0);
    if (l >= ql && r <= qr) return tree[i];

    int mid = (l + r) / 2;
    return merge(query(2 * i, l, mid, ql, qr), query(2 * i + 1, mid + 1, r, ql, qr));
}

signed main() {
    cin >> N >> K;

    vector<int> pos[MXN];
    for (int i = 0; i < MXN; i++)
        pos[i].push_back(-1);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
        pos[A[i]].push_back(i);
    }

    build(1, 0, N - 1);

    int Q;
    cin >> Q;

    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        int candidate = query(1, 0, N - 1, l, r).first;

        if (candidate < 0) {
            cout << "no\n";
            continue;
        }

        auto lb = lower_bound(pos[candidate].begin(), pos[candidate].end(), l);
        lb--;

        auto ub = upper_bound(pos[candidate].begin(), pos[candidate].end(), r);
        ub--;

        int freq = (ub - pos[candidate].begin()) - (lb - pos[candidate].begin());

        if (freq * 2 > r - l + 1) cout << "yes " << candidate << "\n";
        else cout << "no\n";
    }
}