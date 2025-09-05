#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  /* T126 (127plus)
     把每个单词看作一个点, 则可以看作一幅图上起点到终点的最短路
     由于所有边的权重都是1, 这是一个低配版本的最短路
     因此可以使用bfs

     T126:
     在127的基础上, 我们已经知道了到达每一个单词的step(begin为1)
     因此我们可以用一个二维数组存储字符串, 第一维是step
     然后从最大step开始倒序组织序列, 这样可以保证不会出现无效数据
     复杂度算不明白
  */
  vector<vector<string>> findLadders(string beginWord, string endWord,
                                     vector<string> &wordList) {

    int n = wordList.size();
    vector<int> flag(n, 0);

    auto check = [](string s, string t) {
      int len = s.length();
      int flag = 0;
      for (int i = 0; i < len; i++) {
        if (s[i] != t[i]) {
          ++flag;
        }
      }
      return flag == 1;
    };

    vector<vector<string>> temp(n + 3);

    int res = 0;
    queue<pair<string, int>> q;
    q.push(make_pair(beginWord, 1));
    while (q.size()) {
      auto [s, step] = q.front();
      q.pop();
      // 存入temp
      temp[step].push_back(s);
      if (s == endWord) {
        res = step;
        break;
      }
      for (int i = 0; i < n; i++) {
        if (flag[i]) {
          continue;
        }
        if (check(s, wordList[i])) {
          q.push(make_pair(wordList[i], step + 1));
          flag[i] = true;
        }
      }
    }
    vector<vector<string>> ans;
    if (!res) {
      return ans;
    }
    ans.push_back(vector<string>(1, endWord));
    for (int i = res; i > 1; i--) {
      auto temp_ans = ans;
      ans.clear();
      for (auto vec : temp_ans) {
        auto s = vec.back();
        for (auto t : temp[i - 1]) {
          if (check(s, t)) {
            vec.push_back(t);
            ans.push_back(vec);
            vec.pop_back();
          }
        }
      }
    }
    for (auto &vec : ans) {
      reverse(vec.begin(), vec.end());
    }
    return ans;
  }
};

int main() {
  Solution sol;

  return 0;
}
