void inputArray(vi &seq) {
    string s;
    getline(cin, s);
    stringstream inp(s);

    int x;
    while (inp >> x)
        seq.pb(x);
}

void readGrid(vvi &grid) {
    cin.ignore();
    while (true) {
        char s;
        cin >> s;
        vector<int> curr;
        while (true) {
            int x;
            cin >> x;
            curr.pb(x);
            char next;
            cin >> next;
            if (next != ',') break;
        }
        char next;
        grid.pb(curr);
        cin >> next;
        if (next != ',') break;
    }
    cin.ignore();
}

// Don't forget cin.ignore()