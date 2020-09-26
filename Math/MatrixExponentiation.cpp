struct Matrix {
    int a[2][2] = {{0, 0},
                   {0, 0}};

    Matrix operator*(const Matrix &b) const {
        Matrix res;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    res.a[i][j] += a[i][k] * b.a[k][j];
                    res.a[i][j] %= MOD;
                }
            }
        }
        return res;
    }
};

Matrix binpow(Matrix a, int b) {
    Matrix res;
    for (int i = 0; i < 2; i++) res.a[i][i] = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}