#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     *     假设s为一串括号序列, 如 (()())))
     *     我们假定遇到左括号+1, 遇到右括号-1, 起始为0,
     *     则上述括号序列会有这么个前缀和: ( ( ) ( ) ) )  ) 0 1 2 1 2 1 0 -1 -2
     *     于是可以知道一串合法的括号序列的特征:
     *        - 必须以左括号起始
     *        - 相应闭合的右括号, 其前缀和为起始左括号位置前缀和-1
     *        - 起止左右括号之间, 任意位置前缀和都不小于右括号
     *     因此可以确定算法:
     *          - 计算前缀和s
     *          - 记录每个前缀和出现的位置
     *          - 枚举l, 二分查找第一个s[l]-2的位置(即为r+1), 若不存在,
     *     则改为查找最后一个s[l]-1的位置 由于前缀和可能为负数,
     *     因此需要加上len的偏移量(或者把初始前缀和改为len)
     */
    int longestValidParentheses(string s) {
        int len = s.length();
        // idx: idx[-1+len](类型为一个vector) 表示前缀和为-1的位置
        vector<vector<int>> idx((len << 1) + 100);
        vector<int> v(len + 1);
        v[0] = len + 10;
        idx[v[0]].push_back(0);
        // 预处理前缀和位置
        for (int i = 1; i <= len; i++) {
            char c = s[i - 1];
            if (c == '(') {
                v[i] = v[i - 1] + 1;
            } else {
                v[i] = v[i - 1] - 1;
            }
            idx[v[i]].push_back(i);
        }

        int res = 0;
        // 枚举左端点, 计算答案
        for (int i = 1; i <= len; i++) {
            char c = s[i - 1];
            if (c == ')') {
                continue;
            }
            auto vec_pos = idx[v[i] - 2];
            auto tmp = lower_bound(vec_pos.begin(), vec_pos.end(), i);
            if (tmp != vec_pos.end()) {
                int l = i;
                int r = *tmp - 1;
                // cout << l << ' ' << r << endl;
                res = max(res, r - l + 1);
            } else {
                vec_pos = idx[v[i] - 1];
                if (!vec_pos.empty() && vec_pos.back() > 0) {
                    int l = i;
                    int r = vec_pos.back();
                    // cout << l << ' ' << r << endl;
                    res = max(res, r - l + 1);
                }
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    cout << sol.longestValidParentheses(")()())");
}
