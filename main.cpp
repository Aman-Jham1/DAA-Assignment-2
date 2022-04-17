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

  string rnaMolecule;
  cin >> rnaMolecule;
  RNA rna(rnaMolecule);

  Timer timer("Calling RNA secondary structure prediction algorithm");

  
  int ans_top = rna.solve_top_down();
  //int ans_bottom = rna.solve_bottom_up();
  this_thread::sleep_for(chrono::milliseconds(100));

  cout << ans_top << '\n';
  rna.find_path();
  for (auto [i, j] : rna.path) {
      cout << i + 1 << " " << j + 1 << '\n';
  }
  return 0;
}
