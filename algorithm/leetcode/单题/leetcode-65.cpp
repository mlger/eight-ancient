#include <bits/stdc++.h>
using namespace std;

class Solution {
  /* T65
     拆分检验
  */
public:
  bool isNumber(string s) {
    // 检查整数
    auto check_num = [&](string s) {
      if (s == "") {
        return false;
      }
      if (s[0] == '+' || s[0] == '-') {
        s = s.substr(1);
      }
      if (s == "") {
        return false;
      }
      for (auto c : s) {
        if (!isdigit(c)) {
          return false;
        }
      }
      return true;
    };
    // 检查指数部分
    auto check_exp = [&](string s) {
      if (s == "") {
        return true;
      }
      if (s[0] != 'e' && s[0] != 'E') {
        return false;
      }
      return check_num(s.substr(1));
    };
    // 检查十进制数
    auto check_float = [&](string s) {
      if (s == "") {
        return false;
      }
      if (s[0] == '+' || s[0] == '-') {
        s = s.substr(1);
      }
      int len = s.length();
      int dot_pos = -1;
      for (int i = 0; i < len; i++) {
        if (s[i] == '.') {
          dot_pos = i;
          break;
        }
      }
      if (dot_pos == -1 || s.length() == 1) {
        return false;
      }
      for (int i = 0; i < len; i++) {
        if (i == dot_pos) {
          continue;
        }
        if (!isdigit(s[i])) {
          return false;
        }
      }
      return true;
    };
    int len = s.length();
    for (int i = 0; i < len; i++) {
      auto prefix = s.substr(0, i + 1);
      if (check_exp(s.substr(i + 1)) &&
          (check_num(prefix) || check_float(prefix))) {
        return true;
      }
    }
    return false;
  }
};

int main() {}
