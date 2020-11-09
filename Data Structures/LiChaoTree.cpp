template<typename T>
struct LiChaoTree {

    struct Line {
        T slope, yIntercept;

        Line() {
            slope = 0;
            yIntercept = INF;
        }

        Line(T slope, T yIntercept) : slope(slope), yIntercept(yIntercept) {}

        T val(T x) {
            return slope * x + yIntercept;
        }
    };

    struct Node {
        int left, right;
        Line line;

        Node() {
            left = -1;
            right = -1;
        }

        T val(T x) { return line.val(x); }
    };

    T n;
    vector<Node> t;

    void init(T n) {
        this->n = n;
        t.clear();
        t.emplace_back();
        t.emplace_back();
    }

    void create_children(int i) {
        if (t[i].left > -1) return;
        t[i].left = sz(t);
        t.emplace_back();
        t[i].right = sz(t);
        t.emplace_back();
    }

    void insert(int i, T l, T r, Line newLine) {
        T mid = (l + r) >> 1;
        if (newLine.val(mid) < t[i].val(mid)) swap(newLine, t[i].line);
        if (r - l <= 1) return;
        if (newLine.yIntercept >= INF) return;
        create_children(i);
        if (newLine.val(l) <= t[i].val(l)) insert(t[i].left, l, mid, newLine);
        else insert(t[i].right, mid + 1, r, newLine);
    }

    T query(int i, T l, T r, T x) {
        if (r - l <= 1) return t[i].val(x);
        if (t[i].line.yIntercept >= INF) return INF;
        create_children(i);
        T mid = (l + r) >> 1;
        if (x <= mid) return min(t[i].val(x), query(t[i].left, l, mid, x));
        else return min(t[i].val(x), query(t[i].right, mid + 1, r, x));
    }

    void insert(T slope, T yIntercept) { insert(1, 0, n - 1, Line(slope, yIntercept)); }

    T query(T x) { return query(1, 0, n - 1, x); }
};
