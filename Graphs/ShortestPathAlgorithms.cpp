void dijkstra(int src, vi &dist) {
    priority_queue<ii, vector<ii>, greater<>> pq;
    pq.emplace(0, src);

    dist[src] = 0;

    while (!pq.empty()) {
        ii cur = pq.top();
        pq.pop();

        int u = cur.second, curDist = cur.first;
        if (curDist != dist[u]) continue;

        for (const auto &[v, wt] : g[u]) {
            int newDist = curDist + wt;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                pq.emplace(newDist, v);
            }
        }
    }
}

void bfs01(int src, vi &dist) {
    deque<int> dq;
    dq.push_front(src);

    dist[src] = 0;

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (const auto &[v, wt] : g[u]) {
            int newDist = dist[u] + wt;

            if (newDist >= dist[v]) continue;

            dist[v] = newDist;

            if (wt == 1) dq.push_back(v);
            else dq.push_front(v);
        }
    }
}