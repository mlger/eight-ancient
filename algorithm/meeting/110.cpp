#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

/**
 * 给定n个0/1, 以及他们的价值.
 * 消去其中的若干个数, 使得剩下序列不能出现连续110.
 * 求剩余最大价值(mod 1e9+7)
 * 
 * 假设当前枚举到第i个数(1<=i<=n), 即前 i-1 已经决策完毕.
 * f[0/1/2][0/1/2] 表示前i-1个数已经处理完毕, 剩余倒数第二个数为0/1/空, 倒数第一个数为0/1/空的最大价值
 * f[0/1][2] 这种情况不存在
 * 
 * 当前需要决策位置i的数字是否删除
 * 已处理的序列[1-i)的处理结果的表示: 0/1 2表示空
 * 全删了 [2][2]
 * 删剩下一个 [2][0/1]
 * 剩下两个 [0/1][0/1]
 * 
 * f[1, i-1] =>  g[1, i]
 */
int n;
int val[maxn], nums[maxn];
int f[3][3] = {-1};
int g[3][3] = {-1};

long long f[3][3], g[3][3];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> nums[i];
	}

	// 初始情况: 全空为0, 其余全部不存在, 标为-1
	f[2][2] = 0;
	
	for (int i = 1; i <= n; i++) {
		auto x = nums[i];
		// 1. 不保留当前位置
		for (int j = 0; j <= 2; j++) {
			for (int k = 0; k <= 2; k++) {
				g[i][j] = f[i][j];
			}
		}
		// 2. 保留当前位置
		// 2.1 删剩下一个(与当前位置)
		g[2][x] = max(g[2][x], val[i]);

		// 2.2 删剩下两个数字
		if (x == 0) {
			for (int j = 0; j <= 2; j++) {
				for (int k = 0; k <= 2; k++) {
					// 不能拼接110
					if (j == 1 && k == 1) {
						continue;
					}
					// 前置状态需要存在
					if (f[j][k] == -1) {
						continue;
					}
					g[k][x] = max(g[k][x], f[j][k] + val[i]);
				}
			}

		} else {
			// TODO
		}
	}
	
}