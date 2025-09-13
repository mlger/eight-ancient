#include <bits/stdc++.h>
using namespace std;

/*
    给定一个正整数n, 计算有多少个非负整数0<=x<=n, 且满足给定所有m条限制.
    每条限制形如: 将x表示为二进制数, 某一位必须为0/必须为1.
    数据范围:
        1<=n<=2^(2*10^5), 即n至多为2e5位的二进制数, 同时n也以二进制给出
        1<=m<=2e5
        答案对998244353取模

    动态规划, 从高位往低位扫描
    f[i][0/1]表示确定完高[1-i]位, 且第[1-i]位小于/恰好等于n前i位方案数.
    然后进行dp状态转移, 懒得写了.
*/

int main() {
    string N;
    cin >> N;
    int len = N.length();
    vector<int> oo(len + 1, -1);
    int m;
    cin >> m;
    while (m--) {
        int p, o;
        cin >> p >> o;
        p = len - 1 - p;
        if (oo[p] != -1 && oo[p] != o) {
            cout << 0 << endl;
            return 0;
        }
        oo[p] = o;
    }
    vector<long long> f(2, 0), g(2, 0);
    const int mod = 998244353;

    // dp初始化
    auto c0 = N[0];
    if (c0 == '0') {
        if (oo[0] == -1) {
            f[0] = 0;
            f[1] = 1;
        } else if (oo[0] == 0) {
            f[0] = 0;
            f[1] = 1;
        } else if (oo[0] == 1) {
            f[0] = 0;
            f[1] = 0;
        }
    } else {
        if (oo[0] == -1) {
            f[0] = 1;
            f[1] = 1;
        } else if (oo[0] == 0) {
            f[0] = 1;
            f[1] = 0;
        } else if (oo[0] == 1) {
            f[0] = 0;
            f[1] = 1;
        }
    }

    // dp状态转移
    for (int i = 1; i < len; i++) {
        auto c = N[i];
        if (c == '0') {
            if (oo[i] == -1) {
                // 无限定, 该位可选0, 可选1
                g[0] = (f[0] << 1);
                g[0] %= mod;
                g[1] = f[1];
            } else if (oo[i] == 0) {
                // 限定为0
                g[0] = f[0];
                g[1] = f[1];
            } else if (oo[i] == 1) {
                // 限定为1
                g[0] = f[0];
                g[1] = 0;
            } else {
                assert(false);
            }
        } else {
            if (oo[i] == -1) {
                // 无限定, 该位可选0, 可选1
                g[0] = (f[0] * 2) + f[1];
                g[0] %= mod;
                g[1] = f[1];
            } else if (oo[i] == 0) {
                // 该位仅能选0
                g[0] = f[0] + f[1];
                g[0] %= mod;
                g[1] = 0;
            } else if (oo[i] == 1) {
                // 该位仅能选1
                g[0] = f[0];
                g[1] = f[1];
            } else {
                assert(false);
            }
        }
        f[0] = g[0];
        f[1] = g[1];
    }
    auto res = (f[0] + f[1]) % mod;
    cout << res << endl;
}