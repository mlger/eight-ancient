#include <bits/stdc++.h>
using namespace std;

/* T212
   dfs
   状态压缩
   字典树trie上的每个点都有若干状态(x, y, map), xy可以压缩为pos,
   map可以用两个longlong 假设初始是nm个节点, 长度至多为10, 每次至多往四个方向走,
   一共有nm4^10种状态, 这也是我们要枚举的全部
   可以使用bfs或dfs进行枚举
*/
class Solution {
public:
  struct Node {
    Node() : str(""), isWord(false), inque(false) {
      for (int i = 0; i < 26; i++) {
        ch[i] = nullptr;
      }
    }
    Node *ch[26];
    string str;
    vector<pair<int, pair<long long, pair<long long, long long>>>>
        sts; // pos st1(low) st2(hight)
    bool isWord;
    bool inque;
  };

  vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
    vector<string> res;
    Node *Trie = new Node();
    for (auto word : words) {
      Node *now = Trie;
      for (auto c : word) {
        int k = c - 'a';
        if (!now->ch[k]) {
          now->ch[k] = new Node();
        }
        now = now->ch[k];
      }
      now->isWord = true;
      now->str = word;
    }

    int n = board.size();
    int m = board[0].size();

    auto calc_pos = [&n, &m](int x, int y) {
      if (x < 0 || x >= n || y < 0 || y >= m) {
        return -1;
      }
      return x * m + y;
    };

    auto calc_xy = [&n, &m](int pos) {
      int x = pos / m;
      int y = pos % m;
      return make_pair(x, y);
    };

    auto check_st = [&n, &m](pair<long long, pair<long long, long long>> &st,
                             int pos) {
      auto [st1, stt] = st;
      auto [st2, st3] = stt;
      if (pos < 64) {
        return st1 >> pos & 1;
      }
      pos -= 64;
      if (pos < 64) {
        return st2 >> pos & 1;
      }
      pos -= 64;
      return st3 >> pos & 1;
    };

    auto set_st = [&n, &m](pair<long long, pair<long long, long long>> &st,
                           int pos) {
      auto &[st1, stt] = st;
      auto &[st2, st3] = stt;
      if (pos < 64) {
        st1 |= (1ll << pos);
        return;
      }

      pos -= 64;
      if (pos < 64) {
        st2 |= (1ll << pos);
        return;
      }

      pos -= 64;
      st3 |= (1ll << pos);
    };

    // init son of Trie
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        auto c = board[i][j] - 'a';
        auto node = Trie->ch[c];
        if (node) {
          auto st = make_pair(0ll, make_pair(0ll, 0ll));
          int pos = calc_pos(i, j);
          set_st(st, pos);
          node->sts.push_back(make_pair(pos, st));
        }
      }
    }
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    queue<Node *> q;
    // init queue
    for (int i = 0; i < 26; i++) {
      if (Trie->ch[i] && !Trie->ch[i]->sts.empty()) {
        q.push(Trie->ch[i]);
        Trie->ch[i]->inque = true;
      }
    }
    while (q.size()) {
      auto node = q.front();
      q.pop();
      if (node->isWord) {
        res.push_back(node->str);
      }
      // 枚举每个状态, 并且尝试转移
      for (auto [pos, st] : node->sts) {
        auto [x, y] = calc_xy(pos);
        for (int i = 0; i < 4; i++) {
          int tx = x + dx[i];
          int ty = y + dy[i];
          int tpos = calc_pos(tx, ty);
          if (tpos == -1) {
            // 不合法坐标
            continue;
          }
          if (check_st(st, tpos)) {
            // 已访问坐标
            continue;
          }
          auto c = board[tx][ty] - 'a';
          if (!node->ch[c]) {
            // 不在字典(剪枝)
            continue;
          }
          auto tst = st;
          set_st(tst, tpos);
          node->ch[c]->sts.push_back(make_pair(tpos, tst));
          if (!node->ch[c]->inque) {
            q.push(node->ch[c]);
            node->ch[c]->inque = true;
          }
        }
      }
    }
    return res;
  }
};

int main() {

  vector<vector<char>> board({{'a', 'a'}});
  vector<string> words({"aaa"});
  Solution sol;
  auto res = sol.findWords(board, words);
  cout << "res:" << endl;
  for (auto s : res) {
    cout << s << endl;
  }
}
