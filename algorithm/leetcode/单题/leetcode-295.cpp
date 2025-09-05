#include <bits/stdc++.h>
using namespace std;

/* T295
  解法一: 一个大根堆一个小根堆分别保存半个序列.
  解法二: 线段树上二分.
*/
class MedianFinder {
public:
  struct Node {
    Node *l, *r;
    int val;

    Node() : l(nullptr), r(nullptr), val(0) {}
  };

  MedianFinder() {
    siz = 0;
    root = new Node;
  }

  void addNum(int num) {
    // printf("add\n");
    ++siz;
    this->update(root, mint, maxn, num);
  }

  double findMedian() {
    // printf("find\n");
    assert(siz > 0);
    if (siz & 1) {
      int mid = (siz >> 1) + 1;
      return this->query(root, mint, maxn, mid);
    } else {
      int fir = siz >> 1;
      int sec = fir + 1;
      int x = this->query(root, mint, maxn, fir);
      int y = this->query(root, mint, maxn, sec);
      return 1.0 * (x + y) / 2;
    }
  }

private:
  int siz = 0;
  const int mint = -1e5;
  const int maxn = 1e5;
  Node *root;
  void update(Node *rt, int l, int r, int k) {
    assert(rt);
    ++rt->val;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    if (k <= mid) {
      if (!rt->l) {
        rt->l = new Node;
      }
      update(rt->l, l, mid, k);
    } else {
      if (!rt->r) {
        rt->r = new Node;
      }
      update(rt->r, mid + 1, r, k);
    }
  }
  int query(Node *rt, int l, int r, int k) {
    assert(rt);
    if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    if (rt->l && k <= rt->l->val) { // 答案于左区间
      return query(rt->l, l, mid, k);
    }
    // 答案于右区间
    if (rt->l) {
      k -= rt->l->val;
    }
    return query(rt->r, mid + 1, r, k);
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main() {
  MedianFinder medianFinder;
  medianFinder.addNum(1);    // arr = [1]
  medianFinder.addNum(2);    // arr = [1, 2]
  medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
  medianFinder.addNum(3);    // arr[1, 2, 3]
  medianFinder.findMedian(); // return 2.0
  printf("%lf\n", medianFinder.findMedian());
}
