#include <bits/stdc++.h>
using namespace std;
/*
	T2
	一个数x是美丽数, 当且仅当:
		x为正整数
		存在素数p, x%p==0 且 p*p>=x
	
	给定 1<=n<=5e6, 求有多少美丽数<=n

	Solution:
	排除法
	显然, 一个非美丽数x的最大质因子y不超过sqrt(n)
	因此只需要筛选出<=3000的所有素数
	使用深搜可以拼接出这些素数所能凑出的所有整数
	深搜, 从小到大挨个拼接质因子, 然后排除即可

	非美丽数x, 最大质因子y:
		x % y == 0 and y * y < x
		即 x % y == 0 and y < x / y
		这个 x / y 就是拼接 y 之前的那一部分
*/

int n;
int primes[3000], cnt_prime;
int res = 0;

// n根号n筛选质数
void pre(int m = 3000) {
	primes[++cnt_prime] = 2;
	for (int i = 2; i <= m; i++) {
		bool flag = true;
		for (int j = 1; j <= cnt_prime; j++) {
			if (i % primes[j] == 0) {
				flag = false;
				break;
			}
		}
		if (flag) {
			primes[++cnt_prime] = i;
		}
	}
}

// 深度优先搜索
// 当前数字, 当前到第几个质数
void dfs(int now, int now_index) {
	for (int i = now_index; i <= cnt_prime; i++) {
		int prime = primes[i];
		if (1ll * now * prime > n) {
			break;
		}

		// 拼接prime, 如果now > prime, 说明刚好是一个非美丽数
		if (now > prime) {
			++res;
		}
		dfs(now * prime, i);
	}
}


int main() {
	cin >> n;
	res = 1;
	pre();
	dfs(1, 1);
	cout << n - res << endl;
}