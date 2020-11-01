struct PrimeSieve {
    int n;
    vb isPrime;
    vi primes, spf;

    void init(int mx) {
        n = mx + 5;

        isPrime.assign(n, true);
        isPrime[0] = isPrime[1] = false;

        spf.assign(n, 0);

        find_primes();
    }

    void find_primes() {
        for (int i = 2; i * i <= n; i++) {
            if (!isPrime[i]) continue;
            spf[i] = i;
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
                if (!spf[j]) spf[j] = i;
            }
        }

        for (int i = 0; i < n; i++)
            if (isPrime[i])
                primes.pb(i);
    }

    void dump_factors(int x, vector<int> &factors) {
        while (x != 1) {
            factors.pb(spf[x]);
            x /= spf[x];
        }
    }
};