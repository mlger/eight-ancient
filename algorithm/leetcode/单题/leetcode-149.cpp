#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  /*
     n^2枚举斜率, 再来一层数点即可
  */
  int maxPoints(vector<vector<int>> &points) {
    int n = points.size();
    int res = 0;
    if (n == 0) {
      return 0;
    }
    if (n == 1) {
      return 1;
    }
    for (int i = 0; i < n; i++) {
      int x1 = points[i][0];
      int y1 = points[i][1];
      for (int j = i + 1; j < n; j++) {
        int x2 = points[j][0];
        int y2 = points[j][1];
        int tmp = 2;
        for (int k = 0; k < n; k++) {
          if (k == i || k == j) {
            continue;
          }
          int x = points[k][0];
          int y = points[k][1];
          if (x1 == x2) {
            if (x == x1) {
              ++tmp;
            }
          } else if ((x - x1) * (y2 - y1) == (x2 - x1) * (y - y1)) {
            ++tmp;
          }
        }
        res = max(res, tmp);
      }
    }
    return res;
  }
};

int main() {
  Solution sol;

  return 0;
}
