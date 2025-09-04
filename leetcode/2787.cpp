#include <bits/stdc++.h>
using namespace std;

class Solution {
/*
	T2787
	动态规划
 */
   public:
    int numberOfWays(int n, int x) {
		vector<int> qpow(n + 1, 0);
        auto calc_pow = [&](int a) {
            int res = 1;
            for (int i = 0; i < x; i++) {
                res *= a;
                if (res > n) {
                    return -1;
                }
            }
            return res;
        };
		for (int i = 1; i <= n; i++) {
			qpow[i] = calc_pow(i);
		}
        const int mod = 1e9 + 7;

        vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            f[0][i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                auto p = qpow[j];
                f[i][j] = f[i][j - 1];
                if (p != -1 && p <= i) {
                    f[i][j] += f[i - p][j - 1];
                    f[i][j] %= mod;
                }
				cout << "i: " << i <<" j: " << j << " f[i][j]: " << f[i][j] << endl;
            }
        }
        return f[n][n];
    }
};

int main() {
	Solution sol = Solution();
	cout << sol.numberOfWays(10, 2);

}