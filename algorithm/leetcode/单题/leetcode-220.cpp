#include <bits/stdc++.h>
using namespace std;

/*
   类似二维偏序
   首先index天然有序,我们可以使用一个双指针(滑动窗口)枚举所有长度为indexDiff
   的区间.

   那问题就转化为如何判定一个区间nums[l-r], 存在两个数差值不大于
   valueDiff.

   我们将一个区间nums[l-r]的构造视为逐个插入的过程. 那问题就转化为, 插入每个数
   x的时候, 已有数字列表里是否存在[x-valueDiff, x+valueDiff]的数字.

   将滑动窗口的滑动视为从已有数字列表里移除nums[l], 加入nums[r]的操作

   因此我们的数据结构需要支持: 查询某个区间数字是否存在(二分), 单点插入,
   单点删除. 可以使用平衡树(multiset)或者线段树.
*/
class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int indexDiff,
                                     int valueDiff) {
    multiset<int> s;
    int n = nums.size();
    int l = 0, r = min(n - 1, indexDiff);
    for (int i = l; i <= r; i++) {
      int x = nums[i];
      auto it = s.lower_bound(x - valueDiff);
      if (it != s.end() && *it <= x + valueDiff) {
        return true;
      }
      s.insert(x);
    }
    for (; r < n - 1;) {
      // remove old L
      // add new R
      int x = nums[l];
      s.erase(x);
      ++l;
      ++r;
      x = nums[r];
      auto it = s.lower_bound(x - valueDiff);
      if (it != s.end() && *it <= x + valueDiff) {
        return true;
      }
      s.insert(x);
    }
    return false;
  }
};

int main() {
  Solution sol;
  vector<int> vec = {1, 2, 3, 1};
  sol.containsNearbyAlmostDuplicate(vec, 3, 0);
}
