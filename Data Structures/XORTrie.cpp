const int bits = 29;

struct XORTrie {

    struct Node {
        array<int, 2> child;
        int cnt;

        Node() {
            cnt = 0;
            child[0] = -1;
            child[1] = -1;
        }
    };

    vector<Node> t;

    XORTrie() {
        t.emplace_back();
        t.emplace_back();
    };

    void create_children(int i) {
        if (t[i].child[0] > -1) return;

        for (int idx = 0; idx < 2; idx++) {
            t[i].child[idx] = sz(t);
            t.emplace_back();
        }
    }

    void add(int x) {
        int idx = 1;

        for (int bit = bits; bit >= 0; bit--) {
            create_children(idx);

            int visit = (x & (1 << bit)) > 0;

            idx = t[idx].child[visit];
            t[idx].cnt++;
        }
    }

    void remove(int x) {
        int idx = 1;

        for (int bit = bits; bit >= 0; bit--) {
            create_children(idx);

            int visit = (x & (1 << bit)) > 0;

            if (t[t[idx].child[visit]].cnt > 0)
                idx = t[idx].child[visit];
            else break;

            t[idx].cnt--;
        }
    }

    int query(int x) {
        int idx = 1;

        int res = 0;

        for (int bit = bits; bit >= 0; bit--) {
            int visit = ((x & (1 << bit)) > 0) ^ 1;

            create_children(idx);

            if (t[t[idx].child[visit]].cnt > 0) {
                res |= (1 << bit);
                idx = t[idx].child[visit];
            } else idx = t[idx].child[visit ^ 1];
        }

        return res;
    }
};