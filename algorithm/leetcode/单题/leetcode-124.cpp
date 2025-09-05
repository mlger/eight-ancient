#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
  /* T124
    动态规划 f[x] 表示以x为根节点的子树中, 以x为一端所能延伸到的最大路径和
    则有f[x]=max{f[son]}+val[x]
    答案则是max{val[x]+f[son1]+f[son2]}
    由于有负权重, 需要仔细分类
  */
public:
  int res = -0x7fffffff;
  int dfs_f(TreeNode *root) { // 递归地dp, 顺便求答案,返回的是f
    if (!root) {
      return 0;
    }
    int lf = dfs_f(root->left);
    int rf = dfs_f(root->right);
    int f = root->val;
    f = max(f, max(lf, rf) + root->val);
    res = max(res, root->val);
    res = max(res, lf + root->val);
    res = max(res, rf + root->val);
    res = max(res, lf + rf + root->val);
    return f;
  }
  int maxPathSum(TreeNode *root) {
    if (!root) {
      return 0;
    }
    dfs_f(root);
    return res;
  }
};

int main() {
  Solution sol;

  return 0;
}
