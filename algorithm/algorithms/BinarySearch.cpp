#include <bits/stdc++.h>
using namespace std;
int n;
int nums[10];

// 给定一个单调不减的序列, 包含 n 个数字. 给定 x, 求序列中第一个大于等于 x
// 的数字.
int binary_search(int l, int r, int x) {
  if (nums[r] < x) { // 最大值也小于x, 无解
    return -1;
  }
  if (l == r) { // 边界条件, 不可再分, 找到答案
    return nums[l];
  }

  int mid = l + r >> 1;
  if (x <= nums[mid]) { // 答案在左区间
    return binary_search(l, mid, x);
  } else {
    return binary_search(mid + 1, r, x); // 答案在右区间
  }
}

int main() {
  n = 10;
  for (int i = 0; i < 10; i++) {
    nums[i] = (i << 1 | 1);           // {1, 3, 5, 7, ..., 19}
  }
  cout << binary_search(0, 9, 4) << endl;     // output: 5
  cout << binary_search(0, 9, 10) << endl;    // output: 11
  cout << binary_search(0, 9, 22) << endl;    // output: -1
}
