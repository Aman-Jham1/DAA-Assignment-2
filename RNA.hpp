#include <bits/stdc++.h>
using namespace std;

class RNA {
private:
    string rna;
    int n;
    map<char, char> match;
    vector<vector<int>> dp;

public:
    vector<array<int, 2>> path;
    RNA(string S) : rna(S) {
        n = (int)S.size();
        match['A'] = 'U';
        match['U'] = 'A';
        match['G'] = 'C';
        match['C'] = 'G';
        dp.assign(n + 1, vector<int>(n + 1, -1));
    }

    int f(int i, int j) {
        if (j - i < 5)
            return 0;
        int &res = dp[i][j];
        if (res != -1)
            return res;
        res = max(f(i + 1, j), f(i, j - 1));
        for (int t = i + 5; t <= j; ++t) {
            if (match[rna[i]] == rna[t]) {
                res = max(res, 1 + f(i + 1, t - 1) + f(t + 1, j));
            }
        }
        return res;
    }

    int solve_bottom_up() {
        for (int len = 5; len <= n; ++len) {
            for (int i = 0; i < n; ++i) {
                int j = i + len;
                if (j >= n)
                    break;
                dp[i][j] = dp[i + 1][j];
                for (int t = i + 5; t <= j; ++t) {
                    if (match[rna[i]] == rna[t]) {
                        dp[i][j] = max(dp[i][j], dp[i + 1][t - 1] + 1 + dp[t + 1][j]);
                    }
                }
            }
        }
        return dp[0][n - 1];
    }

    void find_path(int i, int j) {
        if (j - i < 5) return;
        int res = f(i, j);
        if (res == f(i + 1, j)) {
            find_path(i + 1, j);
            return;
        }
        if (res == f(i, j - 1)) {
            find_path(i, j - 1);
            return;
        }
        for (int t = i + 5; t <= j; ++t) {
            if (match[rna[i]] == rna[t] and res == 1 + f(i + 1, t - 1) + f(t + 1, j)) {
                path.push_back({i, t});
                find_path(i + 1, t - 1);
                find_path(t + 1, j);
                return;
            }
        }
    }

    int solve_top_down() {
        return f(0, n - 1);
    }

    void find_path() {
        find_path(0, n - 1);
    }

};