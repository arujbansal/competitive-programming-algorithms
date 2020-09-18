struct Sieve {
    int n;
    vector<bool> prime;
    vector<int> primes;

    void init(int x) {
        n = x;
        prime.assign(n + 1, false);
        sieve();
    }

    void sieve() {
        int mx = 1e5;
        prime.assign(mx + 1, true);
        prime[0] = prime[1] = false;
        for (int i = 2; i * i <= mx; i++) {
            if (prime[i]) {
                for (int j = i * i; j <= mx; j += i) prime[j] = false;
            }
        }
        for (int i = 2; i <= n; i++) if (prime[i]) primes.push_back(i);
    }
};