#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  /* T127
     把每个单词看作一个点, 则可以看作一幅图上起点到终点的最短路
     由于所有边的权重都是1, 这是一个低配版本的最短路
     因此可以使用bfs
  */
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    set<string> st;
    for (auto s : wordList) {
      st.insert(s);
    }

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

    queue<pair<string, int>> q;
    q.push(make_pair(beginWord, 1));
    vector<string> temp;
    while (q.size()) {
      auto [s, step] = q.front();
      q.pop();
      if (s == endWord) {
        return step;
      }
      for (auto t : st) {
        if (check(s, t)) {
          temp.push_back(t);
          q.push(make_pair(t, step + 1));
        }
      }
      for (auto t: temp) {
        st.erase(st.find(t));
      }
      temp.clear();
    }
    return 0;
  }
};

int main() {
  Solution sol;

  return 0;
}
