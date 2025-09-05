#include <bits/stdc++.h>
using namespace std;

class Solution {
  /* T76
     双指针, 记录 [l, r] 内每个字符还需要出现的次数(可为负数, 达到0就cnt-1)
     cnt为0时恰好包含
  */
public:
  string minWindow(string s, string t) {
    auto res = make_pair(-1, 123456789);
    vector<int> need(123, 0);
    int cnt = 0;
    for (auto c : t) {
      if (need[c] == 0) {
        ++cnt;
      }
      ++need[c];
    }

    int pre = 0;
    int len = s.length();
    for (int i = 0; i < len; i++) {
      --need[s[i]];
      if (need[s[i]] == 0) {
        --cnt;
      }
      // [pre, i]区间符合
      while (cnt == 0) {
        if (i - pre + 1 < res.second - res.first + 1) {
          res = make_pair(pre, i);
        }
        if (need[s[pre]] == 0) {
          ++cnt;
        }
        ++need[s[pre]];
        ++pre;
      }
      // cout << "pre, i, cnt, res: " << pre << ' ' << i << ' ' << cnt << ' '
      //      << res.first << ' ' << res.second << endl;
    }
    if (res.first == -1) {
      return "";
    }
    return s.substr(res.first, res.second - res.first + 1);
  }
};

int main() {
  Solution sol;
  cout << sol.minWindow("abc", "b") << endl;
  cout << sol.minWindow("b", "b") << endl;
}
