#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  /*  T142: 垃圾题
      直接上题解的解法吧, 仅考虑链表有环的情形.
      1. 先来一个链表

              |-------l------|
              1 -> 2 -> 3 -> 4 -> 5 -> 6
                             ↑    s    ↓
                             9 <- 8 <- 7

         s: 一周的长度
         res: 环的起点

      2. 指针*p从起点出发.
         如果*p进圈了, 则移动的总距离可以表示为:
           sum = l + ks + r (0<=r<s)
      3. 给定两个指针x, y, 从起点出发.
         其中x每次走一步, y每次走两步.

         第一次相遇时.
              容易知道, 从情形一到第一次相遇, x所走的步数r一定是在[0, s)范围内.
              step1 = l + r                 --1
              2 * step1 = l + ns + r        --2
              故x, y分别走了ns, 2ns
         此后.
              在res的步数一定是 l + ks(k>=0).
              此时x走了ns, 再走l即可.
              如何控制这个l呢?
              y从起点重新出发,每次走一步.
              第二次则在res相遇.
  */
public:
  ListNode *detectCycle(ListNode *head) {
    if (!head) {
      return nullptr;
    }
    ListNode *l = head;
    ListNode *r = head;
    int step1, step2;
    l = l->next;
    r = r->next;
    if (r) {
      r = r->next;
    } else {
      return nullptr;
    }
    // first meeting
    while (l != r) {
      if (!r) {
        return nullptr;
      }
      l = l->next;
      r = r->next;
      if (r) {
        r = r->next;
      } else {
        return nullptr;
      }
    }

    // second meeting
    r = head;
    while (l != r) {
      l = l->next;
      r = r->next;
    }
    return l;
  }
};

int main() {
  Solution sol;

  return 0;
}
