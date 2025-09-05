#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
public:
/*
    T295
    对顶堆
    大根堆堆1保存小值, 小根堆堆2保存大值
*/
    priority_queue<int> min_q;
    priority_queue<int,vector<int>,greater<int>> max_q;
    MedianFinder() {
    }
    
    void addNum(int num) {
        // 根据num的值判断进入哪个堆
        if (min_q.size() && num <= min_q.top()) {
            min_q.push(num);
        } else if (max_q.size() && num >= max_q.top()) {
            max_q.push(num);
        } else {
            min_q.push(num);
        }

        // 调整对顶堆大小
        while (min_q.size() > max_q.size() + 1) {
            max_q.push(min_q.top());
            min_q.pop();
        }

        while (max_q.size() > min_q.size()) {
            min_q.push(max_q.top());
            max_q.pop();           
        }
    }
    
    double findMedian() {
        if (min_q.size() == max_q.size()) {
            return 1.0 * (min_q.top() + max_q.top()) / 2;
        } else {
            return min_q.top();
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
