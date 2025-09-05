#include <bits/stdc++.h>
using namespace std;
/*
   把每个范围在[1, n]的整数给整理到正确的位置,
   可以证明这个算法是正确的.
        swap(nums[i], nums[nums[i] - 1]);
   每次swap必定保证nums[i]被整理到了正确的位置,
   此时nums[nums[i]-1]继续整理.整个程序最多执行n次swap.
   每个元素都必定被尝试整理过一次.
*/

class Solution {
public:
  int firstMissingPositive(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      // 只有1到n是有用的
      while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
        swap(nums[i], nums[nums[i] - 1]);
      }
    }
    for (int i = 0; i < n; i++) {
      cout << nums[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }
    return n + 1;
  }
};
int main() {}
