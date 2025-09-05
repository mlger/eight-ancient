# 周赛 439

## T1 [找出最大的几近缺失整数](https://leetcode.cn/problems/find-the-largest-almost-missing-integer/)

```cpp
class Solution {
public:
  /*
     T1
     如果k=1, 则取数组中只出现一次的最大值
     如果k>1, 则只能取第一个或最后一个
     如果k==n, 取最大值
  */
  int largestInteger(vector<int> &nums, int k) {
    if (k == 1) {
      int res = -1;
      unordered_map<int, int> cnt;
      for (auto x : nums) {
        ++cnt[x];
      }
      for (auto x : nums) {
        if (cnt[x] == 1) {
          res = max(res, x);
        }
      }
      return res;
    }
    int n = nums.size();
    if (k == n) {
      int res = -1;
      for (auto x : nums) {
        res = max(res, x);
      }
      return res;
    }

    int x = nums[0], y = nums.back();
    if (x == y && k < n) {
      return -1;
    }
    for (int i = 1; i < n - 1; i++) {
      if (x == nums[i]) {
        x = -1;
      }
      if (y == nums[i]) {
        y = -1;
      }
    }
    return max(x, y);
  }
};
```



## T2 [至多 K 次操作后的最长回文子序列](https://leetcode.cn/problems/longest-palindromic-subsequence-after-at-most-k-operations/)

```cpp
class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        vector<vector<vector<int>>> f(n, vector<vector<int>>(n, vector<int>(k + 1, 0)));
        for (int now = 0; now <= k; now++) {
            for (int len = 1; len <= n; len++) {
                for (int l = 0, r = len - 1; r < n; l++, r++) {
                    if (l == r) {
                        f[l][r][now] = 1;
                    } else {
                        int dis = (s[r] - s[l] + 26) % 26;
                        dis = min(dis, 26 - dis);
                        f[l][r][now] = max(f[l][r - 1][now], f[l + 1][r][now]);
                        if (dis <= now) {
                            f[l][r][now] = max(f[l][r][now], f[l + 1][r - 1][now - dis] + 2);
                        }
                    }
                }
            }
        }
        return f[0][n - 1][k];
    }
};
```

## T3 [长度至少为 M 的 K 个子数组之和](https://leetcode.cn/problems/sum-of-k-subarrays-with-length-at-least-m/)

```cpp
class Solution {
public:
/*
    T3473
    假设f[i][p]表示从[0-i]取p个不重叠子数组的最大和 1<=i<=n
    则f[i][p] = max{f[i-1][p], f[j][p-1] + sum[i]-sum[j]} = sum[i] + max{f[j][p-1]-sum[j]}  0<=j<i
    设g[i][p] = max{f[j][p]-sum[j]} 0<=j<=i
    则f[i][p] = sum[i] + g[i-1][p-1]

    因此可以省略维度p
*/
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        vector<int> f(n + 1, 0);
        vector<int> g(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        g[0] = 0;
        for (int i = 1; i <= n; i++) {
            g[i] = max(g[i-1], -sum[i]);
        }
        while (k--) {
            fill(f.begin(), f.end(), -123456789);
            // for (int i = 0; i <= n; i++)  {
            //     cout<<g[i]<<' ';
            // }cout<<endl;
            for (int i = m; i <= n; i++) {
                f[i] = sum[i] + g[i - m];
                f[i] = max(f[i], f[i - 1]);
            }
            // for (int i = 1; i <= n; i++)  {
            //     cout<<f[i]<<' ';
            // }cout<<endl;

            g[0] = -123456789;
            for (int i = 1; i <= n; i++) {
                g[i] = max(g[i - 1], f[i] - sum[i]);
            }
            // for (int i = 1; i <= n; i++)  {
            //     cout<<g[i]<<' ';
            // }cout<<endl;cout<<endl;
        }
        return f[n];
    }
};
```



## T4 [字典序最小的生成字符串](https://leetcode.cn/problems/lexicographically-smallest-generated-string/)

假定 str2=m

我们首先把 T 的部分进行填充. 填充不了即无解.



接下来是关于 F 的部分. 由于需要字典序最小, 因此我们从左到右进行贪心填充.

- 从前往后遍历所有的 F, 如果已填充的字符可以满足该 F (即已出现不同字符), 则不需要进行填充. 空着就空着, 免得干扰后面的F.

- 如果无可填充, 且无法满足 F, 则无解.

剩下的就需要考虑对 `str1[i]=F`, `l = i`, `r = i + m -1`, [l, r]中的空位进行填充.

可以证明,**[l, r] 中的空位是一个连续的段[x, y]**, 满足l<=x<=y<=r.

y 显然是[l, r]中第一个T的位置pos-1(如果没有, 则y=r) 	因为如果pos为T, 则[pos, pos + m - 1]的部分必定填充了.

由于l之前的填充是连续填充的, 所以找到[l, r]之间第一个空位x, [l, x) 必定是全部填充好的.

且**[l, y] 全是F**

如:

```
m = 3, str2 = abc *表示待填充
FFFFFF
******
```

先看全是F的情况.

考虑[0, 2]的填充, 如果完全不考虑对后面的影响, 贪心填充, 我们肯定是填全'a', 不行就'aa...aab', 这两者至少有一个可以满足第一个F.

To be continue





```cpp
class Solution {
public:
/*
    T3474
    设最终字符串为res
    对于所有str1[i]=='T', res[i-(i+m-1)]==str2, 将res这部分填充好, 如有矛盾则返回""
    此时我们仅需处理剩余的F.
    我们将未填充的空位称为自由位
    枚举F
    取自由段, 并填充为'a'
    如果判重了, 则将最后一个自由位填'b'
    
    证明贪心:
    F有几种情况:
        前缀F
        T后F
        

T后面的第一个F至多有一个自由位, 填'a' 不然填'b'
而且如果该自由位存在, 意味着m所有字符相同
TFFFT
abc
0 1 2 3 4
1 2 3 4

TFFFFFFFT

TFFFT
bab bab


(前缀连续F>=m, 即前m个可以自由选择)
策略: 全部填'a' 如有冲突, 最后一个填'b'
FFFFFT
     0123
xxxx
 xxxx
  xxx0
   xx01
    x012

(前缀连续F<m, 但仍可自由选择)
策略: 全填'a', 如有冲突, 最后一个填'b'
FFFT
   0120
abc0
*/
    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        vector<char> v(n + m - 1, ' ');
        
        // 先解决T(fixed)
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {
                continue;
            }
            for (int j = 0; j < m; j++) {
                if (v[i + j] == ' ') {
                    v[i + j] = str2[j];
                } else if (v[i + j] != str2[j]) {
                    return "";
                }
            }
        }

        // 处理F
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                continue;
            }

            // 先判断有没有冲
            bool flag = true;
            for (int j = 0; j < m && flag; j++) {
                flag &= (v[i + j] == str2[j] || v[i + j] == ' ');
            }
            if (!flag) {
                continue;
            }

            // 没有冲
            int last_index = -1;
            for (int j = 0; j < m; j++) {
                if (v[i + j] == ' ') {
                    last_index = i + j;
                    v[i + j] = 'a';
                }
            }

            // 判断填完a后有没有冲
            flag = true;
            for (int j = 0; j < m && flag; j++) {
                flag &= (v[i + j] == str2[j]);
            }
            // 还是没有冲, 最后一个'a'改'b'
            if (flag) {
                if (last_index == -1) {
                    return "";
                }
                v[last_index] = 'b';
            }
        }

        // 组织答案
        string res = "";
        for (auto c: v) {
            res.push_back(c == ' '? 'a': c);
        }
        return res;
    }
};
```

