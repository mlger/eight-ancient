#include <bits/stdc++.h>
using namespace std;

/* T297
   序列化和反序列化

*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
  // Encodes a tree to a single string.
  // 每个节点化成四位(空节点为null)

  const int bnum[4] = {1000, 100, 10, 1};
  string res;
  vector<int> vals;
  void addnum(int num) {
    num += 1000;
    for (int i = 0; i < 4; i++) {
      res.push_back((num / bnum[i]) % 10 + '0');
    }
    res.push_back(',');
  }
  void addnull() {
    res.push_back('n');
    res.push_back('u');
    res.push_back('l');
    res.push_back('l');
    res.push_back(',');
  }
  void calc(TreeNode *node) {
    if (!node) {
      addnull();
      return;
    }
    addnum(node->val);
    calc(node->left);
    calc(node->right);
  }
  string serialize(TreeNode *root) {
    res = "";
    calc(root);
    return res;
  }

  // Decodes your encoded data to tree.
  TreeNode *decalc(int &cnt) {
    if (vals[cnt] == 2025) {
      ++cnt;
      return nullptr;
    }
    TreeNode *node = new TreeNode(vals[cnt]);
    ++cnt;
    node->left = decalc(cnt);
    node->right = decalc(cnt);
    return node;
  }

  TreeNode *deserialize(string data) {
    vals.clear();
    res = data;
    int len = res.length();
    for (int i = 0; i < len; i += 5) {
      if (res[i] == 'n') {
        vals.push_back(2025);
      } else {
        int x = 0;
        for (int j = 0; j < 4; j++) {
          x = x * 10 + res[i + j] - '0';
        }
        x -= 1000;
        vals.push_back(x);
      }
    }
    int cnt = 0;
    return decalc(cnt);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main() {
  // Solution sol;
  return 0;
}
