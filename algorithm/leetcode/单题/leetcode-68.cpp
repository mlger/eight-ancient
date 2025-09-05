#include <bits/stdc++.h>
using namespace std;

class Solution {
  /* T68
    双指针, 分段分别计算即可
  */

public:
  vector<string> fullJustify(vector<string> &words, int maxWidth) {
    int n = words.size();
    vector<string> res;
    auto solve = [&](int l, int r) {
      cout << "l r: " << l << " " << r << endl;
      // 区间单词数
      int cnt = r - l + 1;
      // 获取区间总长
      int sum_len = 0;
      for (int i = l; i <= r; i++) {
        sum_len += words[i].length();
      }
      // 区间空格数
      int cnt_br = maxWidth - sum_len;
      string s = "";
      if (cnt == 1) { // 单个单词, 补在末尾
        s = words[l];
        for (int i = 0; i < cnt_br; i++) {
          s = s + " ";
        }
      } else {
        int per_br = cnt_br / (cnt - 1);
        int rest_br = cnt_br % (cnt - 1);
        string s_b = "";
        for (int i = 0; i < per_br; i++) {
          s_b += " ";
        }
        for (int i = l; i <= r; i++) {
          s += words[i];
          if (i < r) {
            s += s_b;
          }
          if (rest_br) {
            s += " ";
            --rest_br;
          }
        }
      }
      return s;
    };

    // tmp_size 表示当前区间的总长
    int l = 0, r = 0, tmp_size = 0;
    for (int i = 0; i < n; i++) {
      int len = words[i].size();
      if (tmp_size + len + (i - l) > maxWidth) {
        // 处理当前区间
        r = i - 1;
        res.push_back(solve(l, r));
        // 更新区间
        l = i;
        tmp_size = 0;
      }
      tmp_size += len;
    }
    string s = "";
    for (int i = l; i < n; i++) {
      s += words[i];
      if (i < n - 1) {
        s += " ";
      }
    }
    for (int i = s.length(); i < maxWidth; i++) {
      s = s + " ";
    }
    res.push_back(s);

    return res;
  }
};

int main() {}
