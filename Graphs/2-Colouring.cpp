struct UFDS {
    int n;
    vector<int> info;
 
    UFDS() {}
 
    UFDS(int _n) { init(_n); }
 
    void init(int _n) {
        n = _n;
        info.assign(n, -1);
    }
 
    int get(int x) {
        if (info[x] < 0) return x;
        return info[x] = get(info[x]);
    }
 
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
 
        if (info[x] > info[y])
            swap(x, y);
 
        info[x] += info[y];
        info[y] = x;
 
        return true;    
    }
 
    bool connected(int x, int y) { return get(x) == get(y); }
};
 
struct two_colouring {
    int n;
    UFDS ufds;
    vector<int> answer, in_answer;
 
    two_colouring(int _n) { init(_n); }
 
    void init(int _n) {
        n = _n;
        ufds.init(2 * n);
    }
 
    void add_clause_equal(int x, int y) {
        ufds.unite(x, y);
        ufds.unite(x + n, y + n);
    }
 
    void add_clause_opposite(int x, int y) {
        ufds.unite(x, y + n);
        ufds.unite(x + n, y);
    }
 
    bool satisfiable() {
        for (int i = 0; i < n; i++)
            if (ufds.connected(i, i + n)) return false;
 
        return true;
    }
    
    // Construct an answer where we minimise the number of "which" values in each component
    // which is either 1 or 0
    void construct_answer(int which) {
        answer.resize(n);
        in_answer.assign(2 * n, 0);
        vector<int> cnt(2 * n, 0);

        for (int i = 0; i < 2 * n; i++) 
            cnt[ufds.get(i)] += (i > n) ^ which;

        for (int i = 0; i < n; i++) {
            int cur = ufds.get(i), complement = ufds.get(i + n);

            if (in_answer[cur] || in_answer[complement])
                continue;

            if (cnt[cur] < cnt[complement])
                in_answer[cur] = true;
            else 
                in_answer[complement] = true;
        }

        for (int i = 0; i < n; i++)
            answer[i] = (in_answer[ufds.get(i)] ? 1 : 0);
    }
};