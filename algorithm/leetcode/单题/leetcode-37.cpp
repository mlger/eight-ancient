#include <bits/stdc++.h>
using namespace std;

class Solution {
    /*
     *    待复习: Dancing Links X
     *    普通解法: 搜索+剪枝
     *    预定义函数: calcCol(x, y), calRow(x, y), calBlo(x, y),
     *                用于计算某个坐标对应的行/列/宫
     *    二进制状态压缩数组: atCol[9], atRow[9], atBlo[9],
     *                        atCol[i]>>j&1 表示第i列数字j否已经填了
     *    搜索剪枝
     */
    public:
        const int belBlo[9][9] = {
            {0, 0, 0, 1, 1, 1, 2, 2, 2},
            {0, 0, 0, 1, 1, 1, 2, 2, 2},
            {0, 0, 0, 1, 1, 1, 2, 2, 2},
            {3, 3, 3, 4, 4, 4, 5, 5, 5},
            {3, 3, 3, 4, 4, 4, 5, 5, 5},
            {3, 3, 3, 4, 4, 4, 5, 5, 5},
            {6, 6, 6, 7, 7, 7, 8, 8, 8},
            {6, 6, 6, 7, 7, 7, 8, 8, 8},
            {6, 6, 6, 7, 7, 7, 8, 8, 8},
        };
        int atCol[9], atRow[9], atBlo[9];

        bool dfs(vector<vector<char>> &board) {
            int x = 0, y = 0;
            bool hasEmpty = false;
            for (int i = 0; i < 9 && !hasEmpty; i++) {
                for (int j = 0; j < 9 && !hasEmpty; j++) {
                    if (board[i][j] == '.') {
                        hasEmpty = true;
                        x = i;
                        y = j;
                    }
                }
            }
            if (!hasEmpty) {
                return true;
            }
            // 枚举填入的数
            for (int i = 0; i < 9; i++) {
                if (atRow[x] >> i & 1) {
                    continue;
                }
                if (atCol[y] >> i & 1) {
                    continue;
                }
                if (atBlo[belBlo[x][y]] >> i & 1) {
                    continue;
                }
                // 填数
                atRow[x] |= 1 << i;
                atCol[y] |= 1 << i;
                atBlo[belBlo[x][y]] |= 1 << i;
                board[x][y] = i + 1 + '0';
                if (dfs(board)) {
                    return true;
                }
                // 填数失败, 还原
                atRow[x] ^= 1 << i;
                atCol[y] ^= 1 << i;
                atBlo[belBlo[x][y]] ^= 1 << i;
                board[x][y] = '.';
            }
            return false;
        }

        void solveSudoku(vector<vector<char>> &board) {
            // 预处理棋盘
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (board[i][j] != '.') {
                        int x = board[i][j] - '1';
                        atRow[i] |= (1 << x);
                        atCol[j] |= (1 << x);
                        atBlo[belBlo[i][j]] |= (1 << x);
                    }
                }
            }
            // 搜索
            dfs(board);
        }
};

int main() { Solution sol; }
