#include <bits/stdc++.h>
using namespace std;

class Solution {
  /* T123 -- 买比特币最好的时机是十年前, 其次, 是现在.
     f[i] 表示从第i到n-1天只进行一笔交易, 最大的利润
     g[i] 表示从第0到i天只进行一笔交易, 最大的利润
     先求f[i], g[i]

   */
public:
  int maxProfit(vector<int> &prices) {
    int n = prices.size();
    if (n == 1) {
      return 0;
    } else if (n == 2) {
      return max(0, prices[1] - prices[0]);
    } else if (n == 3) {
      int tmp = max(0, prices[1] - prices[0]);
      tmp = max(tmp, prices[2] - prices[0]);
      tmp = max(tmp, prices[2] - prices[1]);
      return tmp;
    }
    vector<int> lmin(n, 0);
    vector<int> f(n, 0);
    for (int i = 0; i < n; i++) {
      if (i == 0) {
        lmin[i] = prices[i];
        f[i] = 0;
      } else {
        lmin[i] = min(lmin[i - 1], prices[i]);
        f[i] = max(f[i - 1], prices[i] - lmin[i - 1]);
      }
    }
    vector<int> rmax(n, 0);
    vector<int> g(n, 0);
    for (int i = n - 1; i >= 0; i--) {
      if (i == n - 1) {
        rmax[i] = prices[i];
        g[i] = 0;
      } else {
        rmax[i] = max(rmax[i + 1], prices[i]);
        g[i] = max(g[i + 1], rmax[i + 1] - prices[i]);
      }
    }
    int res = max(f[n - 1], g[0]);
    for (int i = 1; i < n - 1; i++) {
      res = max(res, f[i] + g[i + 1]);
    }
    return res;
  }
};

int main() {
  Solution sol;

  return 0;
}
