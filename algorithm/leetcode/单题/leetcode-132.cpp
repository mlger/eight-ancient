#include <bits/stdc++.h>
using namespace std;

class Solution {
  /*
     长度为n的字符串, 共有数量级为n^2的子串
     如果只是朴素的枚举每个子串, 又线性地判断回文串, 显然不可接受
     事实上,子串之间并不是独立的
     使用一个bool数组f[i][j](i<=j),表示区间[i,j]的子串是否是回文串
     g[i]表示s[0-i]分割为全回文串的最小次数
  */
public:
  int minCut(string s) {
    int n = s.length();
    vector<vector<int>> f(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      f[i][i] = true;
    }
    for (int len = 2; len <= n; len++) {
      for (int l = 0, r = l + len - 1; r < n; l++, r++) {
        if (s[l] == s[r]) {
          f[l][r] |= (r == l + 1 || f[l + 1][r - 1]);
        }
      }
    }
    vector<int> g(n, 0x7fffffff);
    g[0] = 0;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < i; j++) {
        if (f[j + 1][i]) { // 可分割
          g[i] = min(g[i], g[j] + 1);
        }
      }
      if (f[0][i]) {
        g[i] = 0;
      }
    }
    return g[n - 1];
  }
};

int main() {
  Solution sol;

  return 0;
}
