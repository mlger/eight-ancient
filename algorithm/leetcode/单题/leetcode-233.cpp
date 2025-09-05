#include <bits/stdc++.h>
using namespace std;

/*
   数位dp
   我们枚举每一位为1的所有可能情况
   处理完最低位, 剩下都好说
   设f(n)表示0<k<=n的所有k中最低位为1的数的和,
    f(n) = (n - 1) / 10 + 1
   然后对于更高位采用类似的算法, 但是需要注意:
    当n的该位为1时, 需要特殊处理
*/
class Solution {
public:
  int countDigitOne(int n) {
    int res = 0;
    auto calc = [](int x) { return (x - 1) / 10 + 1; };
    for (long long i = 1; i <= n; i *= 10) {
      res += calc(n / i) * i;
      if ((n / i) % 10 == 1) {
        res -= i;
        res += n % i + 1;
      }
    }
    return res;
  }
};

int main() {
  Solution sol;
  cout << sol.countDigitOne(13) << endl;
}
