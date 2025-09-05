class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<int> in(n);
        // 计算入度
        for (int i = 0; i < n; i++) {
            if (edges[i] != -1) {
                ++in[edges[i]];
            }
        }

        queue<int> q;
        // topu
        for (int i = 0; i < n; i++) {
            if (!in[i]) {
                q.push(i);
            }
        }
        while (q.size()) {
            int x = q.front();
            q.pop();
            auto y = edges[x];
            if (y != -1) {
                --in[y];
                if (!in[y]) {
                    q.push(y);
                }
            }
        }

        int res = -1;
        for (int i = 0; i < n; i++) {
            if (!in[i]) {
                continue;
            }
            int len = 0;
            int x = i;
            while (in[x]) {
                --in[x];
                x = edges[x];
                ++len;
            }
            res = max(res, len);
        }
        return res;
    }
};
