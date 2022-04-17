#include <bits/stdc++.h>
using namespace std;

/**
 * @brief RNA class
 * 
 */
class RNA {
private:
    string rna; /// given rna molecule
    int n;      /// length of rna molecule 
    unordered_map<char, char> match; /// corresponding base pair matching according to given rules.
    vector<vector<int>> dp;   /// to store cached results

public:
    vector<array<int, 2>> pairs; /// will store the optimal result.
    /**
     * @brief Construct a new RNA object
     * 
     * @param S 
     */
    RNA(string S) : rna(S) {
        n = (int)S.size();
        match['A'] = 'U';
        match['U'] = 'A';
        match['G'] = 'C';
        match['C'] = 'G';
        dp.assign(n + 1, vector<int>(n + 1, -1));
    }

    /**
     * @brief Will be used in top down dp to calculate 
     * result for substring rna(i.......j)
     * 
     * @param i 
     * @param j 
     * @return int 
     */
    int recurse(int i, int j) {
        if (j - i < 5)
            return 0;
        int &res = dp[i][j];
        if (res != -1)
            return res;
        res = max(recurse(i + 1, j), recurse(i, j - 1));
        for (int t = i + 5; t <= j; ++t) {
            if (match[rna[i]] == rna[t]) {
                res = max(res, 1 + recurse(i + 1, t - 1) + recurse(t + 1, j));
            }
        }
        return res;
    }

    /**
     * @brief method to solve the problem in bottom up manner.
     * 
     * @return int 
     */
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
    /**
     * @brief medhod to fond the optimal pairings.
     * 
     * @param i 
     * @param j 
     */

    void find_pairings(int i, int j) {
        if (j - i < 5) return;
        int res = recurse(i, j);
        if (res == recurse(i + 1, j)) {
            find_pairings(i + 1, j);
            return;
        }
        if (res == recurse(i, j - 1)) {
            find_pairings(i, j - 1);
            return;
        }
        for (int t = i + 5; t <= j; ++t) {
            if (match[rna[i]] == rna[t] and res == 1 + recurse(i + 1, t - 1) + recurse(t + 1, j)) {
                pairs.push_back({i, t});
                find_pairings(i + 1, t - 1);
                find_pairings(t + 1, j);
                return;
            }
        }
        return ;
    }

    /**
     * @brief to get the optimal using top down approach.
     * 
     * @return int 
     */
    int solve_top_down() {
        return recurse(0, n - 1);
    }
    /**
     * @brief to get the optimal pairings.
     * 
     */

    void find_pairings() {
        find_pairings(0, n - 1);
    }
};