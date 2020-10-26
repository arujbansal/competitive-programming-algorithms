struct CHT {

    struct Line {
        int slope, yIntercept;

        Line(int slope, int yIntercept) : slope(slope), yIntercept(yIntercept) {}

        int val(int x) {
            return slope * x + yIntercept;
        }

        int intersect(Line y) {
            return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        }
    };

    deque<pair<Line, int>> dq;

    void insert(int slope, int yIntercept) {
        Line newLine(slope, yIntercept);

        while (sz(dq) > 1 && dq.back().second >= dq.back().first.intersect(newLine))
            dq.pop_back();

        if (dq.empty()) {
            dq.emplace_back(newLine, 0);
            return;
        }

        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }

    int query(int x) {

        while (sz(dq) > 1) {
            if (dq[1].second <= x) dq.pop_front();
            else break;
        }

        return dq[0].first.val(x);
    }

    int query2(int x) {
        auto qry = *lower_bound(dq.rbegin(), dq.rend(),
                                make_pair(Line(0, 0), x),
                                [&](const pair<Line, int> &a, const pair<Line, int> &b) {
                                    return a.second > b.second;
                                });

        return qry.first.val(x);
    }
};