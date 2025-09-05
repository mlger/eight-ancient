#include <bits/stdc++.h>
using namespace std;

/* T174
   初始hp显然是越高越有可能通关, 因此可以使用二分
   关键就是这个checker
*/
class Solution {
public:
  int calculateMinimumHP(vector<vector<int>> &dungeon) {
    int n = dungeon.size();
    int m = dungeon[0].size();
    auto check = [&dungeon, &n, &m](int k) {
      vector<vector<int>> rest_hp(n, vector<int>(m, 0));
      if (k + dungeon[0][0] <= 0) {
        return false;
      }
      rest_hp[0][0] = k + dungeon[0][0];
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          auto delta = dungeon[i][j];
          if (i > 0 && rest_hp[i - 1][j] > 0) {
            rest_hp[i][j] = max(rest_hp[i][j], rest_hp[i - 1][j] + delta);
          }
          if (j > 0 && rest_hp[i][j - 1] > 0) {
            rest_hp[i][j] = max(rest_hp[i][j], rest_hp[i][j - 1] + delta);
          }
        }
      }
      return rest_hp[n - 1][m - 1] > 0;
    };

    int l = 1, r = 5e7;
    while (l < r) {
      int mid = l + r >> 1;
      if (check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};

int main() {
  Solution sol;

  return 0;
}
