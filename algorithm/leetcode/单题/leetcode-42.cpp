#include <bits/stdc++.h>
using namespace std;

/*
   某个x的最高水位=min(左侧最高海拔, 右侧最高海拔)
*/
class Solution {
public:
  int trap(vector<int> &height) {
    int n = height.size();
    vector<int> lmax(n), rmax(n);
    for (int i = 0; i < n; i++) {
      if (i == 0) {
        lmax[i] = height[i];
      } else {
        lmax[i] = max(lmax[i - 1], height[i]);
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      if (i == n - 1) {
        rmax[i] = height[i];
      } else {
        rmax[i] = max(rmax[i + 1], height[i]);
      }
    }
    int res = 0;
    for (int i = 1; i < n - 1; i++) {
      int max_level = min(lmax[i - 1], rmax[i + 1]);
      res += max(0, max_level - height[i]);
      cout << max(0, max_level - height[i]) << ' ';
    }
    return res;
  }
};

int main() {}
