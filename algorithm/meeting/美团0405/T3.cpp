#include <bits/stdc++.h>
using namespace std;
/*
	T3
	给定一棵树, 由n-1条带权无向边(x, y, z)构成.
	一条路径长, 即路径所覆盖的所有边的权值和.
	给定m次询问, 每次询问给出x, y, 求包含x, y两点的所有路径中, 最大的路径长.

	dfs1:
		先指定任意节点(1)为根, 然后将边权下放, 赋成点权, val[x]表示x到x父亲的距离.
		求出每个点的直接父亲fa[x][0] = father
		求出每个点到根的路径长度d[x] = d[father] + val[x]
		求出每个点的深度 dep[x] = dep[father] + 1

	dfs2: 树dp
		求出从每个点x出发, 向着子树方向延伸所能达到的最大长度f[x]和次大长度f2[x]
			f[x] = max{f[son] + val[son]}
			f2[x] 类似, 但是是次大值

	dfs3: 换根dp
		求出从每个点x出发, 经过父节点father所能延伸到的最大长度g[x], 这里用到了上面求出来的f[x]和f2[x]
			1. 任意情况, g[x] = val[x] + g[father]
			2. 若f[father]==f[x] + val[x], 说明f[father]是由x推出来的, g[x] = val[x] + f2[father]
			3. 否则g[x] = val[x] + f[father]
		三者中符合条件的取最大值即位g[x]

	pre: 倍增预处理
		fa[x][i] = fa[fa[x][i - 1]][i - 1], 处理出x的2^i级祖先(f[i][0]为直接父亲)
	lca: 倍增求解lca

	calc(x, y): 求解答案
		首先另z = lca(x, y)
		x到y的基础路径长为len = d[x] + d[y] - (d[z] << 1)
		从x往外延伸: 有三个方向:
			1. 往子节点方向延伸, 即f[x]
			2. 往子节点方向延伸, 但f[x]包含在x到y路径中了, 则为f2[x]
			3. 往父节点方向延伸, 即g[x], 需满足 x != z
		三者中符合条件取max即为len1
		从y往外延伸: len2同理
		len + len1 + len2 即最终答案
	
	空间复杂度O(nlogn)
	时间复杂度O(nlogn)
*/

const int maxn = 1e5+5;

int n, m;
vector<vector<pair<int, int>>> edges(maxn);
int val[maxn], d[maxn];
int fa[maxn][20], depth[maxn];
int f[maxn], g[maxn], f2[maxn];

void dfs1(int x, int father) {
	fa[x][0] = father;
	depth[x] = depth[father] + 1;
	d[x] = d[father] + val[x];
	
	for (auto [y, z]: edges[x]) {
		if (y == father) {
			continue;
		}
		// 边权下放
		val[y] = z;
		dfs1(y, x);

	}
}

void dfs2(int x, int father) {
	for (auto [y, z]: edges[x]) {
		if (y == father) {
			continue;
		}
		dfs2(y, x);

		// 状态转移
		if (f[y] + z >= f[x]) {
			f2[x] = f[x];
			f[x] = f[y] + z;
		} else if (f[y] + z > f2[x]) {
			f2[x] = f[y] + z;
		}
	}
}

void dfs3(int x, int father) {
	// 状态转移
	g[x] = g[father] + val[x];
	if (f[father] == f[x] + val[x]) {
		g[x] = max(g[x], f2[father] + val[x]);
	} else {
		g[x] = max(g[x], f[father] + val[x]);
	}

	for (auto [y, z]: edges[x]) {
		if (y == father) {
			continue;
		}
		dfs3(y, x);
	}
}

void pre(int n) {
	for (int i = 1; i < 20; i++) {
		for (int x = 1; x <= n; x++) {
			fa[x][i] = fa[fa[x][i - 1]][i - 1];
		}
	}
}

// 求解(lca, temp_node), temp_node表示: 当x和y是祖先关系(lca==x or lca==y)时, 深度仅次于祖先节点的最后一个节点
pair<int, int> lca(int x, int y) {
	// 假定x为深的那一个
	if (depth[x] < depth[y]) {
		swap(x, y);
	}

	// x往上跳, 直到深度相同
	for (int i = 19; i >= 0; i--) {
		if (depth[fa[x][i]] > depth[y]) {
			x = fa[x][i];
		}
	}

	// 重合, 说明y是x祖先
	if (fa[x][0] == y) {
		return {y, x};
	}

	for (int i = 19; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return {fa[x][0], -1};
}

int calc(int x, int y) {
	// 先处理x, y相等的情况
	if (x == y) {
		return f[x] + max(f2[x], g[x]);
	}

	// 求解lca, 若二者是祖先关系, 则顺便求出路径上最次接近根的一个点
	auto [z, tmp] = lca(x, y);	
	int len = d[x] + d[y] - (d[z] << 1);
	int len1 = 0, len2 = 0;

	if (x != z) {	// x != lca(x, y), 往父节点走不通
		len1 = f[x];
	} else {	// x == lca(x, y), 往父节点或最大子节点或次大子节点走
		len1 = g[x];		// 往父节点走
		if (tmp != -1 && f[tmp] + val[tmp] == f[x]) {	// tmp是最大子节点, 往次大子节点走
			len1 = max(len1, f2[x]);
		} else {
			len1 = max(len1, f[x]);
		}
	}

	if (y != z) {	// x != lca(x, y), 往父节点走不通
		len2 = f[y];
	} else {	// 往父节点或最大子节点或次大子节点走
		len2 = g[y];		// 往父节点走
		if (tmp != -1 && f[tmp] + val[tmp] == f[y]) {	// tmp是最大子节点, 往次大子节点走
			len2 = max(len2, f2[y]);
		} else {
			len2 = max(len2, f[y]);
		}
	}
	return len + len1 + len2;
}

int main() {
	cin >> n >> m;
	for (int i = 1, x, y, z; i < n; i++) {
		cin >> x >> y >> z;
		edges[x].push_back({y, z});
		edges[y].push_back({x, z});
	}
	dfs1(1, 0);
	dfs2(1, 0);
	dfs3(1, 0);
	pre(n);
	
	int x, y;
	while (m--) {
		cin >> x >> y;
		cout << calc(x, y) << endl;
	}
	return 0;

}