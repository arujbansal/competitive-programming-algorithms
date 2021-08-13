#include <bits/stdc++.h>
 
using namespace std;
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, Q;
    cin >> N >> Q;
 
    vector<int> A(N);
    for (auto &x : A)
        cin >> x;
 
    vector<int> lg(N + 1); // lg[i] = log2(i)
    lg[1] = 0;
    for (int i = 2; i <= N; i++)
        lg[i] = lg[i / 2] + 1;
 
    // sparse[i][j] : Minimum value in the interval [j, j + 2^i - 1]
    vector sparse(lg[N] + 1, vector<int>(N));
 
    for (int j = 0; j < N; j++)
        sparse[0][j] = A[j];
 
    for (int i = 1; i <= lg[N]; i++)
        for (int j = 0; j + (1 << i) - 1 < N; j++) // (1 << x) = 2^x
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
 
    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
 
        int i = lg[r - l + 1];
        cout << min(sparse[i][l], sparse[i][r - (1 << i) + 1]) << "\n";
    }
}