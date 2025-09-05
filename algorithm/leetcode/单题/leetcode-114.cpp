class Solution {
public:
/*
    LCR 114
    相邻两个单词x<y, 三种情况:
    1. xy相同x是y的前缀, 得不出任何结论
    2. y是x的前缀, 无解
    3. x, y存在第一个位置, 使得字符不同, 记该位置x, y字符分别为c1, c2, 则有c1 < c2

    从c1向c2连一条有向边
*/
    string alienOrder(vector<string>& words) {
        vector<vector<int>> v(26);
        vector<int> in(26);

        auto resolve = [&](string &x, string &y) {
            int len1 = x.length();
            int len2 = y.length();
            for (int i = 0; i < len1 && i < len2; i++) {
                if (x[i] != y[i]) {
                    v[x[i] - 'a'].push_back(y[i] - 'a');
                    ++in[y[i] - 'a'];
                    return true;
                }
            }
            if (len1 > len2) {
                return false;
            }
            return true;
        };

        // 建图
        int n = words.size();
        for (int i = 0; i < n - 1; i++) {
            if (!resolve(words[i], words[i + 1])) {
                return "";
            }
        }

        // topu排序
        vector<int> res;
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if(!in[i]) {
                res.push_back(i);
                q.push(i);
            }
        }

        while (q.size()) {
            auto x = q.front();
            q.pop();
            for (auto y: v[x]) {
                --in[y];
                if (!in[y]) {
                    res.push_back(y);
                    q.push(y);
                }
            }
        }
        
        for (int i = 0; i < 26; i++) {
            if (in[i]) {
                return "";
            }
        }

        // 寻找原words中出现的字符
        int flag = 0;
        for (auto word: words) {
            for (auto c: word) {
                flag |= (1 << (c - 'a'));
            }
        }
        // 组织答案
        string res_str = "";
        for (auto x: res) {
            if (flag >> x & 1) {
                res_str.push_back('a' + x);
            }
        }
        return res_str;

    }
};
