#include <bits/stdc++.h>
using namespace std;

/*
  dp: f[i][j] 表示s[0-i] p[0-j] 是否能匹配(bool)
  关键在于p
  状态转移, 对于p[j]=char(c)
    - c == '?'
        f[i][j] |= f[i-1][j-1]
    - c == '*'
        f[i][j] |= f[k][j-1](k<=i)   -- 任意序列(包含空)
*/
class Solution {
public:
  bool isMatch(string s, string p) {
    s = "%" + s;
    p = "%" + p;
    int n = s.size(), m = p.size();
    vector<vector<int>> f(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (p[j] == '*') {
          f[i][j] |= f[i][j - 1]; // 空
          if (i > 0) {
            f[i][j] |= f[i - 1][j];
          }
        } else if (p[j] == '?' || s[i] == p[j]) {
          if (i > 0 && j > 0) {
            f[i][j] |= f[i - 1][j - 1];
          } else if (i == 0 && j == 0) {
            f[i][j] = true;
          }
        }
      }
    }
    return f[n - 1][m - 1];
  }
};

int main() {}

