#include <bits/stdc++.h>

using namespace std;

const string BASE = "ACGU";

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "w", stdout);
    srand(static_cast<unsigned>(time(0)));
    int len = 100;
    int n = rand() % len + 1;
    n = 1000;
    string s;

    for (int i = 0; i < n; ++i) {
        int cur = rand() % 4;
        s.push_back(BASE[cur]);
    }

    cout << s << '\n';
    return 0;
}