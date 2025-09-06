#include <bits/stdc++.h>
using namespace std;

/**
    给定长度为n的序列a, 将其重排为a'.
    bi=MEX(a'1,a'2,a'3,...,a'i). 要最大化b元素之和.
    输入:
        第一行一个n (1<=n<=2e5)
        第二行n个数, 表示序列ai (0<=ai<=1e9)
    输出:
        第一行一个数, 表示b最大和
        第二行n个数, 表示重拍后的序列a', 输出任意合法解即可.

    这么考虑
    既然整个重拍后序列a'的MEX已知, 因此所有子序列的mex必定不大于最大的这个MEX
    因此a'的前缀应当尽量早凑出这个最大MEX
*/

const int maxn = 2e5 + 5;
int n;
int a[maxn];
bool flag[maxn];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    int mex = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == mex) {
            flag[i] = true;
            ++mex;
        }
    }
    long long res = 1ll * mex * (mex + 1) / 2 + 1ll * (n - mex) * mex;
    cout << res << endl;
    for (int i = 1; i <= n; i++) {
        if (flag[i]) {
            cout << a[i] << ' ';
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!flag[i]) {
            cout << a[i] << ' ';
        }
    }
    cout << endl;
}
