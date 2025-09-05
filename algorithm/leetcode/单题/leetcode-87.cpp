#include <bits/stdc++.h>
using namespace std;

class Solution {
  /* T87
     题目描述的是一个递归的过程
     倒过来看,从一个一个字符拼到最初始的字符串
     其实是多次两个区间合并的过程,只不过合并的两个区间可能换了位置
     因此可以区间dp
     f[i][j][k][l] 表示s1[i-j] s2[k-l] 能否符合题意
  */
public:
  bool f[31][31][31][31];
  bool isScramble(string s1, string s2) {
    int n = s1.length();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (s1[i] == s2[j]) {
          f[i][i][j][j] = true;
        }
      }
    }
    for (int len = 2; len <= n; len++) { // 要计算的区间长
      for (int l1 = 0, r1 = l1 + len - 1; r1 < n; l1++, r1++) {
        for (int l2 = 0, r2 = l2 + len - 1; r2 < n; l2++, r2++) {
          for (int k = 1; k < len; k++) { // 必须分割成两个非空串
            int mid1 = l1 + k - 1;
            int mid2 = l2 + k - 1;
            int mid3 = l2 + (len - k) - 1;
            f[l1][r1][l2][r2] |=
                (f[l1][mid1][l2][mid2] && f[mid1 + 1][r1][mid2 + 1][r2]);
            f[l1][r1][l2][r2] |=
                (f[l1][mid1][mid3 + 1][r2] && f[mid1 + 1][r1][l2][mid3]);
          }
        }
      }
    }
    return f[0][n - 1][0][n - 1];
  }
};

int main() {
  Solution sol;

  return 0;
}
