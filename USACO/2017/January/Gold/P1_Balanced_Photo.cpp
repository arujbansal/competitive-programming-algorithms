/*
 * USACO 2017 January Contest, Gold
 * Problem 1. Balanced Photo
 * Problem Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(nullptr)
#define setIO(i, o) freopen(i, "r", stdin), freopen(o, "w", stdout)
#define trav(e, x) for (auto &e : x)
#define pb(x) push_back(x)
#define eb(x...) emplace_back(x)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
#define lc(i) 2*i
#define rc(i) 2*i+1
//#define int long long
using namespace std;
using namespace __gnu_pbds;
using vi = vector<int>;
using ii = pair<int, int>;
using ht = gp_hash_table<int, int>;

struct SegmentTree {
    vector<int> t;
    int n;

    void init(int x) {
        n = x;
        t.assign(2 * n, 0);
    }

    static int merge(int x, int y) { return x + y; }

    void modify(int p) {
        for (t[p += n]++; p /= 2;) t[p] = merge(t[lc(p)], t[rc(p)]);
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) res = merge(res, t[l++]);
            if (r & 1) res = merge(res, t[--r]);
        }
        return res;
    }

};

signed main() {
    FAST_IO;
    setIO("bphoto.in", "bphoto.out");

    int n;
    cin >> n;
    vi a(n), a2(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a2[i] = a[i];
    }
    sort(all(a2));
    map<int, int> val;
    int last = 1;
    trav(x, a2) if (val[x] == 0) val[x] = last++;
    trav(x, a) x = val[x] - 1;

    SegmentTree invL, invR;
    invL.init(n), invR.init(n);
    int cnt[n][2];
    for (int i = 0, j = n - 1; i < n; i++, j--) {
        cnt[i][0] = invL.query(a[i], n);
        invL.modify(a[i]);
        cnt[j][1] = invR.query(a[j], n);
        invR.modify(a[j]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int l = cnt[i][0], r = cnt[i][1];
        if (max(l, r) > 2 * min(l, r)) ans++;
    }
    cout << ans;
}
