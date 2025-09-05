#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  /*
    dp: f[i] 表示s[0-i]可拆分成的答案,然后凑就好了
        复杂度很大, 懒得算.
  */
  vector<string> wordBreak(string s, vector<string> &wordDict) {
    int n = s.length();
    set<string> dict(wordDict.begin(), wordDict.end());
    vector<vector<string>> res(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        string temp_str = s.substr(j, i - j + 1);
        if (dict.find(temp_str) != dict.end()) {
          if (j == 0) {
            res[i].push_back(temp_str);
          } else {
            for (auto tmp : res[j - 1]) {
              res[i].push_back(tmp + " " + temp_str);
            }
          }
        }
      }
    }
    return res[n - 1];
  }
};

int main() {
  Solution sol;

  return 0;
}
