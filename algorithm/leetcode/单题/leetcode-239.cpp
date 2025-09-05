#include <bits/stdc++.h>
using namespace std;

/*
   ST表(最合适的解法)
   设lmx[x][i]表示x向右(包括x)2^i个元素的最大值
    lmx[x][0]=nums[x]
    lmx[x][i]=max(lmx[x][i-1], lmx[x+(1<<(i-1))][i-1])
   右边也一样, 构造的复杂度是nlogn的
   然后对于区间[l,r], 我们容易计算出长度的对数 k=floor(log2(r-l))
   然后lmx[l][k], rmx[r][k]夹一下就好了

   线段树

   平衡树
   这里偷个懒, 用平衡树, 啥时候再补ST表的代码吧.
*/
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    multiset<int> s;
    vector<int> res;
    for (int i = 0; i < k; i++) {
      s.insert(nums[i]);
    }
    int n = nums.size();
    for (int l = 0, r = k - 1; r < n;) {
      res.push_back(*s.rbegin());
      cout<<s.size();
      s.erase(s.find(nums[l]));
      ++l, ++r;
      if (r < n) {
        s.insert(nums[r]);
      }
    }
    return res;
  }
};

int main() { Solution sol; 

  vector<int> vec = {-7,-8,7,5,7,1,6,0};
  sol.maxSlidingWindow(vec, 4);
}
