#include <bits/stdc++.h>
using namespace std;

/* T51
   1<=n<=9
   由于n较小, 可以n!枚举全排列(至多362880种情况, 然后O(n^2)判定即可)
   判定时只需
*/
class Solution {
public:
  vector<vector<string>> solveNQueens(int n) {
    string normal_str = "";
    for (int i = 0; i < n; i++) {
      normal_str = normal_str + ".";
    }

    // 判断对角线是否冲突
    auto check = [&](vector<int> v) {
      int len = v.size();
      assert(len == n);
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (i - j == v[i] - v[j] || i - j + v[i] - v[j] == 0) {
            return false;
          }
        }
      }
      return true;
    };
    // 组织答案
    auto gen_str = [&](vector<int> v) { // v从1开始
      vector<string> temp(n, normal_str);
      for (int i = 0; i < n; i++) {
        temp[i][v[i] - 1] = 'Q';
      }
      return temp;
    };


    vector<int> v;
    for (int i = 1; i <= n; i++) {
      v.push_back(i);
    }
    vector<vector<string>> res;
    // 全排列算法
    do {
      if (check(v)) {
        res.push_back(gen_str(v));
      }
    } while (next_permutation(v.begin(), v.end()));
    return res;
  }
};

int main() {}
