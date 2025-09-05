#include <bits/stdc++.h>
using namespace std;

class Solution {
  /* T115
    f[i][j] 表示s[0-i]的子序列中出现t[0-j]的个数
    容易所以第一维可以滚掉
    倒序遍历甚至可以直接不要
  */

public:
  int numDistinct(string s, string t) {
    int n = s.length();
    int m = t.length();
    const int mod = 1e9 + 7;
    vector<long long> f(m, 0);
    for (char c : s) {
      for (int i = m - 1; i >= 0; i--) {
        if (c == t[i]) {
          if (i == 0) {
            ++f[i];
            f[i] %= mod;
          } else {
            f[i] += f[i - 1];
            f[i - 1] %= mod;
          }
        }
      }
    }
    return f[m - 1];
  }
};

int main() {
  Solution sol;

  return 0;
}
