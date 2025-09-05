#include <bits/stdc++.h>
using namespace std;

/* T282

   假设每个间隙有四种情况+-*和''. 边插入,边求值.
*/
class Solution {
public:
  string str_num;
  int len;
  int target;
  vector<string> res_strs;

  void dfs(int index, int now_num, int mul_num, int res, char pre_op,
           string &res_str) {
    if (index == len) {
      if (index == 10 && 1ll * mul_num * now_num > 0x7fffffff) {
        return;
      }
      mul_num *= now_num;
      if (pre_op == '+') {
        res = res + mul_num;
      } else if (pre_op == '-') {
        res = res - mul_num;
      }
      if (res == target) {
        res_strs.push_back(res_str);
      }
      return;
    }
    int num = 0;
    if (now_num == -1) {
      num = str_num[index] - '0';
    } else if (now_num == 0) { // 不能有前导0
      return;
    } else {
      // 爆int
      if (index == 9 &&
          1ll * now_num * 10 + str_num[index] - '0' > 0x7fffffff) {
        return;
      }
      num = now_num * 10 - '0' + str_num[index];
    }
    // res_str = res_str + str_num[index]; // res_str
    res_str.push_back(str_num[index]);

    // 继续往下算, 无添加符号
    dfs(index + 1, num, mul_num, res, pre_op, res_str);

    if (index == len - 1) {
      res_str.pop_back();
      return;
    }

    // 添加'*'
    mul_num *= num;
    res_str.push_back('*');
    dfs(index + 1, -1, mul_num, res, pre_op, res_str);
    res_str.pop_back();

    if (pre_op == '+') {
      res = res + mul_num;
    } else if (pre_op == '-') {
      res = res - mul_num;
    }

    // 添加'+'
    res_str.push_back('+');
    dfs(index + 1, -1, 1, res, '+', res_str);
    res_str.pop_back();
    // 添加'-'
    res_str.push_back('-');
    dfs(index + 1, -1, 1, res, '-', res_str);
    res_str.pop_back();

    res_str.pop_back();
  }

  vector<string> addOperators(string num, int target) {
    this->str_num = num;
    this->len = num.size();
    this->target = target;
    string res_str = "";
    dfs(0, -1, 1, 0, '+', res_str);
    return this->res_strs;
  }
};

int main() {
  Solution sol;
  // sol.addOperators("232", 8);
  sol.addOperators("2147483647", 2147483647);
  return 0;
}
