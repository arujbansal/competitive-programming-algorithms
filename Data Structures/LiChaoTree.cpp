template<typename T>
struct LiChaoTree {

    struct Line {
        T slope, yIntercept;

        Line() {
            slope = 0;
            yIntercept = INF;
        }

        Line(T slope, T yIntercept) : slope(slope), yIntercept(yIntercept) {}

        T val(int x) {
            return slope * x + yIntercept;
        }
    };

    struct Node {
        Node *lChild, *rChild;
        Line line;

        Node() {
            lChild = NULL;
            rChild = NULL;
        }

        T val(int x) { return line.val(x); }

        void create_children() {
            if (lChild != NULL) return;
            lChild = new Node();
            rChild = new Node();
        }
    };

    int n;
    Node *root;

    void init(int n) {
        this->n = n;
        root = new Node();
    }

    void insert(Node *i, int l, int r, Line newLine) {
        int mid = (l + r) >> 1;
        if (newLine.val(mid) < i->val(mid)) swap(newLine, i->line);
        if (r - l <= 1) return;
        i->create_children();
        if (newLine.val(l) <= i->val(l)) insert(i->lChild, l, mid, newLine);
        else insert(i->rChild, mid + 1, r, newLine);
    }

    T query(Node *i, int l, int r, T x) {
        if (r - l <= 1) return i->val(x);
        i->create_children();
        int mid = (l + r) >> 1;
        if (x <= mid) return min(i->val(x), query(i->lChild, l, mid, x));
        else return min(i->val(x), query(i->rChild, mid + 1, r, x));
    }

    void insert(T slope, T yIntercept) { insert(root, 0, n - 1, Line(slope, yIntercept)); }

    T query(int x) { return query(root, 0, n - 1, x); }
};