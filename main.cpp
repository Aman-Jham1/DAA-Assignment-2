/**
 * @file main.cpp
 * @author Aman Jham
 * @author Jay Patel
 * @author Kruti Baraiya
 * @author Zaeem Ansari
 * @brief Given an RNA molecule, predict its secondary structure.
 * @version 0.1
 * @date 2022-04-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
#include "RNA.hpp"

using namespace std;
using namespace chrono;

/**
 * Structure to measure the running time of algorithm
 */
struct Timer {
    string name{""};
    time_point<high_resolution_clock> end, start{high_resolution_clock::now()};
    std::chrono::duration<float, std::milli> duration;
    Timer() = default;
    Timer(string name) : name(name) {}
    ~Timer()
    {
        end = high_resolution_clock::now();
        duration = end - start;
        cout << "@" << name << "> " << duration.count() << " ms" << '\n';
    }
};

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  freopen("./Test/input.txt", "r", stdin);
  freopen("./Test/output.txt", "w", stdout);

  /**
   * @brief input RNA molecule.
   * 
   */
  string rnaMolecule;
  cin >> rnaMolecule;

  /**
   * @brief instantiate the object.
   * 
   */

  RNA rna(rnaMolecule);

  Timer timer("Calling RNA secondary structure prediction algorithm");

  /**
   * @brief Calling top down method to find the optimum pairings.
   * 
   */
  int ans_top = rna.solve_top_down();
  //int ans_bottom = rna.solve_bottom_up();
  this_thread::sleep_for(chrono::milliseconds(100));

  cout << ans_top << '\n';

  rna.find_pairings();

  /**
   * @brief Printing the optimal pairs.
   * 
   */

  for (auto [i, j] : rna.pairs) {
      cout << i + 1 << " " << j + 1 << '\n';
  }
  return 0;
}
