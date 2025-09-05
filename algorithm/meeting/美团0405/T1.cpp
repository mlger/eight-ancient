#include <bits/stdc++.h>
using namespace std;
/*
	T1
	给定m次查询, 每次给定 1<=l<=r<=int_max
	初始值 x=l, 给定 w1, w2 分别表示将 x 乘以2, 乘以3的单次代价.
	求最小代价, 使得 x>=r

	Solution:
	枚举乘以多少次2, 然后求还差乘以多少次3
	复杂度mlog^2(INTMAX), 不知道能不能过
*/

int solve(int l, int r, int w1, int w2) {
	int cost1 = 0;
	// 单次复杂度log平方
	int res = 0;
	
	// 枚举乘以0到若干个2
	for (long long now = l; now <= r; now++) {
		// 求还差多少个3
		long long tmp = now;
		int cost2 = 0;
		while (tmp <= r) {
			tmp *= 3;
			cost2 += 3;
		}
		res = min(res, cost1 + cost2);

		// 求差多少个3
		cost1 += w1;
		now *= 2;
	}
	res = min(res, cost1);
	return res;
}
int main() {
	int m;
	cin >> m;
	int l, r, w1, w2;
	while (m--) {
		cin >> l >> r >> w1 >> w2;
		cout << solve(l, r, w1, w2) << endl;
	}
}