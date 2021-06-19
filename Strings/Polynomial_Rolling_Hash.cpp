template<typename T>
struct polynomial_hash {
    int n;
    string s;
    T m, b; // prime mod, base
    vector<T> hash, inverse; // hash[i] : hash value of s[0, i - 1]

    polynomial_hash() {}

    polynomial_hash(const string &_s, T _m, T _b) {
        init(_s, _m, _b);
    }
    
    void init(const string &_s, T _m, T _b) {
        s = _s;
        n = (int) (s.size());
        m = _m;
        b = _b;
        hash.resize(n + 1);
        inverse.resize(n + 1);
        precompute();
    }

    T binpow(T x, T y) {
        T res = 1;
        while (y > 0) {
            if (y % 2 != 0) res = (res * x) % m;
            x = (x * x) % m;
            y /= 2;
        }

        return res;
    }

    // Builds the hash and inverse array
    void precompute() {
        T power = b;
        hash[0] = 0;
        for (int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] + (s[i - 1] - 'a' + 1) * power) % m;
            power = (power * b) % m;
        }

        inverse[n] = binpow(binpow(b, n), m - 2);
        for (int i = n - 1; i > 0; i--)
            inverse[i] = (inverse[i + 1] * b) % m;
    }

    // Returns the hash value of substring s[l, r]
    T get_hash(int l, int r) {
        l++, r++;
        if (l == 1) return hash[r];
        return ((((hash[r] - hash[l - 1]) % m) + m) * inverse[l - 1]) % m;
    }
};