class Solution:
    def quick_pow(self, x: int, y: int, mod: int = 1000000007):
        res = 1
        while y > 0:
            if y & 1:
                res *= x
                res %= mod
            x *= x
            x %= mod
            y >>= 1
        return res

    def productQueries(self, n: int, queries: list[list[int]]) -> list[int]:
        """
        1. 先将n按照二进制进行拆分为f0, f1, f2..., 获取数组f
        2. 获取幂指数组g=log2f 
        3. 将g进行前缀和
        4. 快速幂取模即可
        """
        cnt = 30
        g = []
        while n:
            if n >= (1 << cnt):
                g.append(cnt)
                n -= (1 << cnt)
            cnt -= 1
        g.reverse()
        #print(g)

        for i in range(1, len(g)):
            g[i] += g[i - 1]
        #print(g)

        res = []
        for [l, r] in queries:
            cnt = g[r] if l == 0 else g[r] - g[l - 1]
            res.append(self.quick_pow(2, cnt))
        return res


if __name__ == '__main__':
    sol = Solution()
    n = 15
    queries = [[0, 1], [2, 2], [0, 3]]
    print(sol.productQueries(n, queries))
