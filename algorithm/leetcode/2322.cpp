#include <bits/stdc++.h>
using namespace std;

class Solution {
    /**
     * T2322
     *	一棵树断两条边, 分割为三棵树. 求三棵子树节点权值异或和中, 较大者与较小者差值的最小值.

	 *  Solution:
	 *  n <= 1000, 先求出以任意节点x为根的子树异或和f[x] 枚举任意两个节点x, y, 断掉其与父亲的连边. 分两种情况:
     *		1. x, y为父子关系, 则异或和分别为 f[x], f[y]^f[x], f[root]^f[y]
     *		2. x, y 不为父子关系, 则异或和分别为 f[x], f[y], f[root]^f[x]^f[y]
	 * 	如何判断x, y是否是父子关系?
     *	使用欧拉序(节点先序遍历顺序)
	 *  id[x] < id[y] < id[x]+size[x], 表示y在x子树内
     */
   public:
    int n = 0, root = 0, cnt = 0;
    int res = 0x7fffffff;
    vector<int> f, siz, id;

    // dfs 获取子树异或和
    void dfs(vector<vector<int>>& v, vector<int>& nums, int x, int fa) {
        f[x] = nums[x];
        siz[x] = 1;
        id[x] = ++cnt;
        for (auto y : v[x]) {
            if (y == fa) {
                continue;
            }
            dfs(v, nums, y, x);
            f[x] ^= f[y];
            siz[x] += siz[y];
        }
    }

    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        root = 0;
        n = nums.size();
        f.resize(n);
        id.resize(n);
        siz.resize(n);
        vector<vector<int>> v(n);
        for (auto vec : edges) {
            v[vec[0]].push_back(vec[1]);
            v[vec[1]].push_back(vec[0]);
        }
        dfs(v, nums, root, -1);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (i == root || j == root) {  // 根节点无法断边
                    continue;
                }
                auto x = i, y = j;
                if (id[x] > id[y]) {
                    swap(x, y);
                }
                int val1, val2, val3;
                if (id[y] <= id[x] + siz[x] - 1) {  // y在x子树
                    val1 = (f[x] ^ f[y]);
                    val2 = f[y];
                    val3 = (f[root] ^ f[x]);
                } else {
                    val1 = f[x];
                    val2 = f[y];
                    val3 = (f[root] ^ f[x] ^ f[y]);
                }
                auto mint = min(val1, min(val2, val3));
                auto maxx = max(val1, max(val2, val3));
                res = min(res, maxx - mint);
            }
        }
		return res;
    }
};

int main() {}