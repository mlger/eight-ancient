#include <bits/stdc++.h>
using namespace std;

class Solution {
  /* T214
     题意即: 找到当前字符串的最大回文前缀串
     如果枚举每个前缀串[0-mid-[char(c)]-l-r]
     则我们需要判定 s[0-m] == s[r-l]
     使用一个具有前缀和性质的哈希函数
     hash[x] = hash[x-1] * k + s[x];
     hash[l - r] = hash[r] - hash[l - 1] * (k^(r-l+1))
  */
public:
  string shortestPalindrome(string s) {
    int n = s.length();
    vector<long long> lhash1(n + 1, 0);
    vector<long long> lhash2(n + 1, 0);
    vector<long long> lhash3(n + 1, 0);
    vector<long long> rhash1(n + 1, 0);
    vector<long long> rhash2(n + 1, 0);
    vector<long long> rhash3(n + 1, 0);
    const long long mod1 = 1e9 + 7;
    const long long mod2 = 998244353;
    const long long mod3 = 114514;
    const long long t1 = 53;
    const long long t2 = 131;
    const long long t3 = 123;
    for (int i = 0; i < n; i++) {
      if (i == 0) {
        lhash1[i] = s[i];
        lhash2[i] = s[i];
        lhash3[i] = s[i];
      } else {
        lhash1[i] = lhash1[i - 1] * t1 + s[i];
        lhash1[i] %= mod1;
        lhash2[i] = lhash2[i - 1] * t2 + s[i];
        lhash2[i] %= mod2;
        lhash3[i] = lhash3[i - 1] * t3 + s[i];
        lhash3[i] %= mod3;
      }
    }

    for (int i = n - 1; i >= 0; i--) {
      rhash1[i] = rhash1[i + 1] * t1 + s[i];
      rhash1[i] %= mod1;
      rhash2[i] = rhash2[i + 1] * t2 + s[i];
      rhash2[i] %= mod2;
      rhash3[i] = rhash3[i + 1] * t3 + s[i];
      rhash3[i] %= mod3;
    }

    auto quick_pow = [](int x, int y, long long mod) {
      long long res = 1;
      for (; y; y >>= 1) {
        if (y & 1) {
          res *= x;
          res %= mod;
        }
        x = 1ll * x * x % mod;
      }
      return res;
    };

    auto check_pal = [&](int p) {
      if (p == 0) {
        return true;
      }
      int mid = p >> 1;
      int l = mid + 1, r = p;
      if (!(p & 1)) {
        --mid;
      }
      long long h1 = rhash1[l] - rhash1[r + 1] * quick_pow(t1, r + 1 - l, mod1);
      h1 = (h1 % mod1 + mod1) % mod1;
      long long h2 = rhash2[l] - rhash2[r + 1] * quick_pow(t2, r + 1 - l, mod2);
      h2 = (h2 % mod2 + mod2) % mod2;
      long long h3 = rhash3[l] - rhash3[r + 1] * quick_pow(t3, r + 1 - l, mod3);
      h3 = (h3 % mod3 + mod3) % mod3;
      return h1 == lhash1[mid] && h2 == lhash2[mid] && h3 == lhash3[mid];
    };

    for (int i = n - 1; i >= 0; i--) {
      if (check_pal(i)) {
        if (i == n - 1) {
          return s;
        }
        auto temp = s.substr(i + 1);
        reverse(temp.begin(), temp.end());
        return temp + s;
      }
    }
    return "";
  }
};

int main() {
  Solution sol;
  cout << sol.shortestPalindrome("aab") << endl;
  cout << sol.shortestPalindrome("aacecaaa") << endl;
  cout << sol.shortestPalindrome("aab") << endl;
}
