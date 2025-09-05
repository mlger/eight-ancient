#include <bits/stdc++.h>
using namespace std;

/**
 * 快速幂取模
 * 给定a, b, p (1 <= a, b, p <= 10^9), 求a的b次幂对p取余的结果
*/

int quick_pow(int a, int b, int p) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			res = 1ll * res * a % p;
		}
		a = 1ll * a * a % p;
	}
	return res;
}

int main() {

}