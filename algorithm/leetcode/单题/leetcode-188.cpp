#include <bits/stdc++.h>
using namespace std;

/* T188
    类似于背包
    先预处理任意区间[l, r]在r卖掉的最大利润profit[l, r]
    先预处理出任意[l, r]内如果有某笔交易的最大利润max_profit[l, r]
    有
      max_profit[l, r] = max{profit[l, k]} (l<=k<=r)
    设定f[k][i]为区间[1-i]所进行k笔交易的最大利润
    则有
      f[k][i] = max{f[k-1][j]+profit[j+1][i]}(0<=j<i)

    事实上, 第一个维度可以滚掉, 类似于背包, 即
      f[i] = max{f[j]+max_profit[j+1][i], f[i]}(0<=j<i)
      倒序更新即可
    复杂度O(kn^2) 等待优化


*/
class Solution {
public:
  int maxProfit(int k, vector<int> &prices) {
    int n = prices.size();

    vector<vector<int>> profit(n, vector(n, 0));
    for (int l = 0; l < n; l++) {
      int in_minx = prices[l];
      for (int r = l; r < n; r++) {
        in_minx = min(in_minx, prices[r]);
        profit[l][r] = prices[r] - in_minx;
      }
    }

    vector<vector<int>> max_profit(n, vector(n, 0));
    for (int l = 0; l < n; l++) {
      for (int r = l; r < n; r++) {
        max_profit[l][r] = profit[l][r];
        if (r > l) {
          max_profit[l][r] = max(max_profit[l][r], max_profit[l][r - 1]);
        }
      }
    }

    vector<int> f(n, 0);
    for (; k; k--) {
      for (int i = n - 1; i > 0; i--) {
        f[i] = max(f[i], max_profit[0][i]);
        for (int j = 0; j < i; j++) {
          f[i] = max(f[i], f[j] + max_profit[j + 1][i]);
        }
      }
    }
    return f.back();
  }
};

int main() {
  // Solution sol;

  return 0;
}
