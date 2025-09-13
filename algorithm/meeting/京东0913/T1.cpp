#include <bits/stdc++.h>
using namespace std;

/*
    给定一长度为n的序列, 可以进行k次操作, 每次操作选定一数字增大1.
   求最小化最终序列, 相邻元素差的绝对值的最大值.

    分析:
    1. ai只能增大, 不能减小. 意味着最大值是否就无需操作?
    2. 如果一小一大相邻, 需要减小差距, 只能上升小的.
    3. 那意味着最大的定住了, 次大的只需要满足最大的要求, 也即可固定.
    4. 使用大跟堆, 从大数值位置开始, 判断左右位置是否应当抬升.
    5. nice.
*/

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int max_index = 1;
    vector<int> version(n + 1, 0);
    vector<int> b(n + 1, 0);

    auto check = [&](int m) {
        int copy_k = k;
        priority_queue<pair<int, pair<int, int>>> q;
        // 1. 拷贝a数组, 清空版本号, 构建初始堆
        for (int i = 1; i <= n; i++) {
            version[i] = 0;
            b[i] = a[i];
            q.push({b[i], {i, version[i]}});
        }
        while (q.size()) {
            auto [x, pii] = q.top();
            auto [index, ver] = pii;
            q.pop();
            if (ver < version[index]) {
                // 过时数据
                continue;
            }
            if (index > 1) {
                int sub1 = b[index] - b[index - 1];
                if (sub1 > m) {
                    copy_k -= (sub1 - m);
                    b[index - 1] = b[index] - m;
                    ++version[index - 1];
                    q.push({b[index - 1], {index - 1, version[index - 1]}});
                }
            }
            if (index < n) {
                int sub2 = b[index] - b[index + 1];
                if (sub2 > m) {
                    copy_k -= (sub2 - m);
                    b[index + 1] = b[index] - m;
                    ++version[index + 1];
                    q.push({b[index + 1], {index + 1, version[index + 1]}});
                }
            }
            if (copy_k < 0) {
                return false;
            }
        }
        return true;
    };

    int l = 0, r = 1e9;
    while (l < r) {
        auto mid = l + r >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
