#include <bits/stdc++.h>
using namespace std;

/*
  核心是实现表达式的转换: 将中缀表达式转换为后缀表达式(逆波兰式)
      1 + 2 * 3 + 4
      1 2 3 * 4 + +
  1. 遇到数字: 直接入结果栈
  2. 遇到符号:
        a. 左括号: 直接入符号栈
        b. 右括号: 符号栈栈顶不断出栈并进入结果栈, 直到遇到左括号. 将左括号出栈.
        c. 符号: 符号栈栈顶不断出栈并进入结果栈, 直到栈顶优先级更低, 或栈空
        d. 左右括号优先级最低
        e. 负号: 在前面补0



  实现难点在于字符串的处理
*/
class Solution {
public:
  int calculate(string s) {
    string num_str = "";
    int n = s.length();
    // 提取token流
    vector<pair<int, int>> tokens;
    auto to_num = [](string &s) {
      int x = 0;
      for (auto c : s) {
        x = x * 10 - '0' + c;
      }
      return x;
    };

    auto isvalid = [](char c) {
      return isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' ||
             c == '(' || c == ')';
    };
    for (int i = 0; i < n; i++) {
      while (i < n && !isvalid(s[i])) {
        ++i;
      }
      if (i == n) {
        break;
      }
      if (!isdigit(s[i])) {
        if (s[i] == '-' &&
            ((tokens.empty() ||
              (tokens.back().first == 0 && tokens.back().second == '(')))) {
          tokens.push_back(make_pair(1, 0));
        }
        tokens.push_back(make_pair(0, s[i]));
      } else {
        int r = i;
        for (; r < n && isdigit(s[r]); ++r) {
        }
        --r;
        num_str = s.substr(i, r - i + 1);
        i = r;
        tokens.push_back(make_pair(1, to_num(num_str)));
      }
    }

    int fir[255] = {0};
    fir['('] = 0;
    fir[')'] = 0;
    fir['+'] = 1;
    fir['-'] = 1;
    fir['*'] = 2;
    fir['/'] = 2;
    vector<pair<int, int>> s_res;
    stack<char> s_op;
    // 转后缀表达式
    for (auto [op, num] : tokens) {
      if (op == 0) {
        auto c = (char)num;
        if (c == '(') {
          s_op.push(c);
        } else if (c == ')') {
          while (s_op.top() != '(') {
            s_res.push_back(make_pair(0, s_op.top()));
            s_op.pop();
          }
          s_op.pop();
        } else {
          while (!s_op.empty() && fir[s_op.top()] >= fir[c]) {
            s_res.push_back(make_pair(0, s_op.top()));
            s_op.pop();
          }
          s_op.push(c);
        }
      } else {
        s_res.push_back(make_pair(1, num));
      }
    }
    while (!s_op.empty()) {
      s_res.push_back(make_pair(0, s_op.top()));
      s_op.pop();
    }

    // 打印后缀表达式
    // for (auto [op, num] : s_res) {
    //   if (op == 0) {
    //     cout << (char)num << ' ';
    //   } else if (op == 1) {
    //     cout << num << ' ';
    //   }
    // }
    // cout << endl;
    // 求值
    stack<int> res;
    for (auto [op, num] : s_res) {
      if (op == 0) {
        int y = res.top();
        res.pop();
        int x = res.top();
        res.pop();
        int z = 0;
        if (num == '+') {
          z = x + y;
        } else if (num == '-') {
          z = x - y;
        } else if (num == '*') {
          z = x * y;
        } else if (num == '/') {
          z = x / y;
        }
        res.push(z);
      } else if (op == 1) {
        res.push(num);
      }
    }
    return res.top();
  }
};

int main() {
  Solution sol;
  cout << sol.calculate("1 + 1") << endl;
  cout << sol.calculate(" 2-1 + 2 ") << endl;
  cout << sol.calculate("(1+(4+5+2)-3)+(6+8)") << endl;
  cout << sol.calculate("2147483647") << endl;
  cout << sol.calculate("1 - (-2)") << endl;
}
