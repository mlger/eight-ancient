#include <bits/stdc++.h>
using namespace std;

/* T3
   设原始串拆成数字数组a0 ... an an+1
   最终x=sum{ai*Cni}  y=sum{ai+1*Cni}
   于是问题转化为验证 x%10 == y%10
   即 10 | x-y
   即 10 | sum{(ai-ai+1)*Cni}
   x % 10 == 0  iff  x % 2 == 0 && x % 5 == 0
   只需快速求出 Cni%2 和 Cni%5, 用卢卡斯定理
*/

class Solution {
public:
  int c[10][10];

  void prework() {
    memset(c, 0, sizeof c);
    c[0][0] = 1;
    for (int i = 1; i <= 9; i++) {
      for (int j = 0; j <= i; j++) {
        if (j == 0) {
          c[i][j] = 1;
        } else {
          c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
      }
    }
  }

  int calc_lucas(int n, int m, int p) {
    if (n < m) {
      return 0;
    }
    if (n < 5 && m < 5) {
      return c[n][m] % p;
    }
    if (m == 0) {
      return 1;
    }
    return calc_lucas(n / p, m / p, p) * c[n % p][m % p] % p;
  }

  bool hasSameDigits(string s) {
    prework();

    vector<int> v;
    v.clear();
    for (auto c : s) {
      v.push_back(c - '0');
    }
    int n = v.size() - 2;
    for (int i = 0; i <= n; i++) {
      v[i] = v[i] - v[i + 1];
      v[i] += 10;
      v[i] %= 10;
    }

    int res2 = 0, res5 = 0;
    for (int i = 0; i <= n; i++) {
      res2 += v[i] * calc_lucas(n, i, 2);
      res2 %= 2;

      res5 += v[i] * calc_lucas(n, i, 5);
      res5 %= 5;
    }
    return res2 == 0 && res5 == 0;
  }
};

int main() {
  Solution sol;
  cout << sol.hasSameDigits(
              "0300022427060081338593250228812416852360779367560633538982691027"
              "1362510821237981765801422499370463489650101764740244267931439415"
              "2469836346236005574117397927599269857689932900084323655981889677"
              "7372446044173183745892603635662475843891406965512332502771798073"
              "9876942536805954677442624037463336729467")
       << endl;

  return 0;
}
