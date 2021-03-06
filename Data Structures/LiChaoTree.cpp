template<typename T> 
struct li_chao_min {
    static const T identity = numeric_limits<T>::max();

    struct Line {
        T m, c;

        Line() {
            m = 0;
            c = identity;
        }

        Line(T m, T c) : m(m), c(c) {}

        T val(T x) { return m * x + c; }
    };

    struct Node {
        Line line;
        Node *lc, *rc;

        Node() : lc(0), rc(0) {}        
    };

    T L, R, eps;
    deque<Node> buffer;
    Node* root;

    Node* new_node() {
        buffer.emplace_back();
        return &buffer.back();
    }

    void init(T L, T R, T eps) {
        this->L = L;
        this->R = R;
        this->eps = eps;

        root = new_node();
    }

    void insert(Node* &cur, T l, T r, Line line) {
        if (!cur) {
            cur = new_node();
            cur->line = line;
            return;
        }

        T mid = l + (r - l) / 2;
        if (r - l <= eps) return;

        if (line.val(mid) < cur->line.val(mid))
            swap(line, cur->line);

        if (line.val(l) < cur->line.val(l)) insert(cur->lc, l, mid, line);
        else insert(cur->rc, mid + 1, r, line);
    }

    int query(Node* &cur, T l, T r, T x) {
        if (!cur) return identity;

        T mid = l + (r - l) / 2;
        T res = cur->line.val(x);
        if (r - l <= eps) return res;

        if (x <= mid) return min(res, query(cur->lc, l, mid, x));
        else return min(res, query(cur->rc, mid + 1, r, x));
    }

    void insert(T m, T c) { insert(root, L, R, Line(m, c)); }

    int query(T x) { return query(root, L, R, x); }
};