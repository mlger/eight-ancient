# 快速幂

```
int quick_pow(int x, int y, int p) {
	if (x == 0) {
		return 0;
	}
	int res = 1;
	for(; y; y>>=1) {
		if (y & 1) {
			res = 1ll * res * x % p;
		}
		x = 1ll * x % p;
	}
	return x;	
}
```



# 费马小定理

$a^{p-1}\equiv 1(modp)$, p为质数

2. 乘法逆元

$a^{-1}\equiv a^{p-2}(modp)$

```cpp
int main() {
  int p = 1e9 + 7;
  vector<int> flac(100, 1);
  // 预处理阶乘
  for (int i = 1; i <= 20; i++) {
    flac[i] = 1ll * flac[i - 1] * i % p;
  }

  // 费马小定理求逆元
  auto inv = [&](int x) { return quick_pow(x, p - 2, p); };

  // 求组合数
  auto C = [&](int n, int m) {
    int x = flac[m] * flac[n - m] % p; // 分母
    return flac[n] * inv(x) % p;
  };
  for (int i = 0; i <= 20; i++) {
    cout << C(20, i) << ' ';
  }
  cout << endl;
  return 0;
}

```

# 拓扑排序

情景: 有向无环图

topu排序

可以用来找环, 很多时候也会结合dp

https://leetcode.cn/problems/Jf1JuT/description/

https://leetcode.cn/problems/longest-cycle-in-a-graph/description/



# 二分

lower_bound	upper_bound

