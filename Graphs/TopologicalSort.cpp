struct TopologicalSort {
    vector<int> order;
    vector<bool> working, done;
    int top;

    TopologicalSort(int n) {
        top = n - 1;
        order.resize(n);
        working.assign(n, false);
        done.assign(n, false);
    }

    void topo_sort(int u) {
        if (working[u]) {
            cout << "-1\n";
            exit(0);
        }
        working[u] = true;
        for (const auto &v:  g[u]) if (!done[v]) topo_sort(v);
        working[u] = false;
        done[u] = true;
        order[top--] = u;
    }
};