#include <bits/stdc++.h>
using namespace std;

class Solution {
  /*
     贪心
     评分低的孩子先分配糖果
     分配数max(1, 左右两侧更低分糖果数+1, 左右两侧同分糖果数)
  */
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
      s.insert(make_pair(ratings[i], i));
    }
    vector<int> res(n, 0);
    int ans = 0;
    for (auto [rating, pos] : s) {
      res[pos] = 1;
      if (pos > 0) {
        if (ratings[pos - 1] < rating) {
          res[pos] = max(res[pos], res[pos - 1] + 1);
        }
      }
      if (pos < n - 1) {
        if (ratings[pos + 1] < rating) {
          res[pos] = max(res[pos], res[pos + 1] + 1);
        }
      }
      ans += res[pos];
    }
    return ans;
  }
};

int main() {
  Solution sol;

  return 0;
}
