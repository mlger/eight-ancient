# T1 & T3

```
class Solution {
public:
  /*
     T1 T3
     线段树
  */

  struct node {
    node *lson;
    node *rson;
    int val;

    node() : lson(nullptr), rson(nullptr), val(-1) {}
  };

  unordered_map<int, bool> mp;

  void update(node *p, int l, int r, int k, int val) {
    if (l == r) {
      p->val = val;
      return;
    }
    int mid = l + r >> 1;
    if (k <= mid) {
      if (!p->lson) {
        p->lson = new node();
      }
      update(p->lson, l, mid, k, val);
    } else {
      if (!p->rson) {
        p->rson = new node();
      }
      update(p->rson, mid + 1, r, k, val);
    }
    p->val = -1;
    if (p->lson) {
      p->val = max(p->val, p->lson->val);
    }
    if (p->rson) {
      p->val = max(p->val, p->rson->val);
    }
  }

  int query(node *p, int l, int r, int u, int v, int k) {
    if (!p) {
      return -1;
    }
    if (p->val < k) {
      return -1;
    }
    if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    int res = -1;
    if (u <= mid && p->lson && p->lson->val >= k) {
      return query(p->lson, l, mid, u, v, k);
    }
    if (v > mid && p->rson && p->rson->val >= k) {
      return query(p->rson, mid + 1, r, u, v, k);
    }
    return -1;
  }

  int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets) {
    node *rt = new node();

    int n = fruits.size();
    for (int i = 0; i < n; i++) {
      update(rt, 0, n, i, baskets[i]);
    }
    int res = 0;
    for (auto x : fruits) {
      auto tmp = query(rt, 0, n, 0, n, x);
      if (tmp == -1) {
        ++res;
      } else {
        update(rt, 0, n, tmp, -1);
      }
    }
    return res;
  }
};
```

# T2

```
class Solution {
public:
  /*
     堆+贪心
  */
  vector<long long> findMaxSum(vector<int> &nums1, vector<int> &nums2, int k) {

    int n = nums1.size();
    auto cmp = [&](int i, int j) { return nums1[i] < nums1[j]; };
    vector<int> idxs;
    for (int i = 0; i < n; i++) {
      idxs.push_back(i);
    }
    sort(idxs.begin(), idxs.end(), cmp);

    priority_queue<int, vector<int>, greater<int>> q;
    vector<long long> res(n, 0);
    long long now_sum = 0;
    for (int i = 0; i < n;) {
      int j = i;
      for (; j < n && nums1[idxs[j]] == nums1[idxs[i]]; j++) {  // 统计答案
        res[idxs[j]] = now_sum;
      }

      for (j = i; j < n && nums1[idxs[j]] == nums1[idxs[i]]; j++) {     // 更新堆
        int y = nums2[idxs[j]];
        if (q.size() < k) {
          q.push(y);
          now_sum += y;
        } else if (y > q.top()) {
          now_sum -= q.top();
          q.pop();
          q.push(y);
          now_sum += y;
        }
      }
      i = j;
    }
    return res;
  }
};
```

# T4

```
class Solution {
public:
/*
    T3480
    先不考虑删除
    我们要求区间[l, r], 使得其中不包含任何冲突对(x, y)的个数
    从小到大枚举r, 遇到冲突对 y <= r, 就将其左端点加入, 然后求最大值 mx. 则区间(mx, r] 都是可以取的, 共 r - mx 个

    接下来考虑删除冲突对 (x, y), 会使得原先哪些不合法的区间变得合法?
    考虑重新计算答案, 此时仅删除最大左端点会使得答案变大, 变大的值是最大左端点到次大左端点的距离
    将该增益算到被删除的冲突对上
*/
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        // 先将冲突调整为左 < 右
        for (auto &v: conflictingPairs) {
            if (v[0] > v[1]) {
                swap(v[0], v[1]);
            }
        }
        // 冲突对按照右端点排序
        auto cmp = [](vector<int> &x, vector<int> &y) {
            return x[1] < y[1];
        };
        sort(conflictingPairs.begin(), conflictingPairs.end(), cmp);

        int lmax1 = -1;  // 左端点最大值id
        int lmax2 = -1;  // 左端点次大值id
        int m = conflictingPairs.size();
        vector<long long> addition(m, 0);
        int now = 0;
        long long res = 0;
        long long max_addition = 0;
        for (int i = 1; i <= n; i++) {
            while (now < m && conflictingPairs[now][1] == i) {
                if (lmax1 == -1) {
                    lmax1 = now;
                } else if (conflictingPairs[now][0] >= conflictingPairs[lmax1][0]) {

                    lmax2 = lmax1;
                    lmax1 = now;
                } else if (lmax2 == -1 || conflictingPairs[now][0] > conflictingPairs[lmax2][0]) {
                    lmax2 = now;
                }
                ++now;
            }
            // 计算答案
            if (lmax1 == -1) {
                res += i;
            } else {
                res += i - conflictingPairs[lmax1][0];
            }
            // 计算增量
            if (lmax1 != -1) {
                if (lmax2 == -1) {
                    addition[lmax1] += conflictingPairs[lmax1][0];
                } else {
                    addition[lmax1] += conflictingPairs[lmax1][0] - conflictingPairs[lmax2][0];
                }
                max_addition = max(max_addition, addition[lmax1]);
            }
        }
        return res + max_addition;
    }
};


```
