#include <bits/stdc++.h>
using namespace std;

/**
    一套试卷包含多个x-dp算法, 求本质不同的x-dp算法类型数目. (如adp和bdp就是不同的x-dp算法)
    保证s可以被唯一分割为一个或多个形如x+dp的段

    输入:
        s(3<=len(s)<=10^6)
    输出:
        x-dp类型数

    示例1:
        输入:
            sosdpadp
        输出:
            2
    
    示例2:
        输入:
            adpbdpadp
        输出:
            2

    字符串记录当前已存在的哈希值
*/

string s;
int n;
set<pair<int, int>> st;
const int mod1 = 1e9 + 7, h1 = 13;
const int mod2 = 998244353, h2 = 337;
int main() {
    cin >> s;
    n = s.length();
    long long hash1 = 0, hash2 = 0;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (i < n - 1 && s[i] == 'd' && s[i + 1] == 'p') {
            if (i != 0) {
                auto pii = make_pair(hash1, hash2);
                if (st.find(pii) == st.end()) {
                    st.insert(pii);
                    ++res;
                }
                hash1 = 0;
                hash2 = 0;
            }
            ++i;
            continue;
        }
        hash1 *= h1;
        hash1 += s[i];
        hash1 %= mod1;
        hash2 *= h2;
        hash2 += s[i];
        hash2 %= mod2;
    }
    cout << res << endl;
}
