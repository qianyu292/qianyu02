#include<functional>
#include<stdexcept>
#include<vector>
#include<string>
using namespace std;
struct SegmentNode {
	int l, r;
	int mergeval;
	SegmentNode* left;
	SegmentNode* right;
	SegmentNode(int mergeval, int l, int r) :mergeval(mergeval), l(l), r(r), left(nullptr),
		right(nullptr) {
	}
};
class SegmentTree {
private:
	SegmentNode* root;
	function<int(int, int)>merger;

	SegmentNode* build(const vector<int>& nums, int l, int r)
	{
		if (l == r)
		{
			return new SegmentNode(nums[l], l, r);
		}
		int mid = l + (r - l) / 2;
		SegmentNode* left = build(nums, l, mid - 1);
		SegmentNode* right = build(nums, mid + 1, r);
		SegmentNode* node = new SegmentNode(merger(left->mergeval, right->mergeval), l, r);

		node->left = left;
		node->right = right;
		return node;
	}
	void update(SegmentNode* node, int index, int value)
	{
		if (node->l == node->r)
		{
			node->mergeval = value;
		}
		int mid = node->l + (node->r - node->l) / 2;
		if (index < mid)
		{
			update(node->left, index, value);
		}
		else
		{
			update(node->right, index, value);
		}
		node->mergeval = merger(node->left->mergeval, node->right->mergeval);
	}
	int query(SegmentNode* node, int qL, int qR)
	{
		if (node->l == qL && node->r == qR)
		{
			return node->mergeval;
		}

		int mid = node->l + (node->r - node->l) / 2;
		if (qR <= mid) {
			// node.l <= qL <= qR <= mid
			// 目标区间完全在左子树中
			return query(node->left, qL, qR);
		}
		else if (qL > mid) {
			// mid < qL <= qR <= node.r
			// 目标区间完全在右子树中
			return query(node->right, qL, qR);
		}
		else {
			// node.l <= qL <= mid < qR <= node.r
			// 目标区间横跨左右子树
			// 将查询区间拆分成 [qL, mid] 和 [mid + 1, qR] 两部分，分别向左右子树查询
			// 最后将左右子树的查询结果合并
			return merger(
				query(node->left, qL, mid),
				query(node->right, mid + 1, qR)
			);
		}
	}
public:
	SegmentTree(const vector<int>& nums, function<int(int, int)> merger)
		: merger(merger) {
		root = build(nums, 0, nums.size() - 1);
	}
	void update(int index, int value) {
		update(root, index, value);
	}

	int query(int qL, int qR) {
		return query(root, qL, qR);
	}
};
//数组实现
class ArraySegmentTree {
private:
	vector<int>tree;

	int n;

	function<int(int, int)>merger;

	int leftchild(int node)
	{
		return 2 * node + 1;
	}
	int rightchild(int node)
	{
		return 2 * node + 2;
	}
	void build(const vector<int>& nums, int l, int r, int rootIndex) {
		if (l == r)
		{
			tree[rootIndex] = nums[l];
		}
		int mid = l + (r - l) / 2;
		int leftrootIndex = leftchild(rootIndex);
		int rightrootIndex = rightchild(rootIndex);

		build(nums, l, mid, leftrootIndex);

		build(nums, mid + 1, r, rightrootIndex);

		tree[rootIndex] = merger(tree[leftrootIndex], tree[rightrootIndex]);
	}
	void update(int l, int r, int rootIndex, int index, int value)
	{
		if (l == r) {
			// 找到了目标叶子节点，更新值
			tree[rootIndex] = value;
			return;
		}
		int mid = l + (r - l) / 2;
		if (index <= mid) {
			// 若 index 较小，则去左子树更新
			update(l, mid, leftchild(rootIndex), index, value);
		}
		else {
			// 若 index 较大，则去右子树更新
			update(mid + 1, r, rightchild(rootIndex), index, value);
		}

		// 后序位置，左右子树已经更新完毕，更新当前节点的聚合值
		tree[rootIndex] = merger(tree[leftchild(rootIndex)], tree[rightchild(rootIndex)]);
	}
	int query(int l, int r, int rootIndex, int qL, int qR) {
		if (l == qL && r == qR)
		{
			return tree[rootIndex];
		}
		int mid = l + (r - l) / 2;
		int leftRootIndex = leftchild(rootIndex);
		int rightRootIndex = rightchild(rootIndex);
		if (qR <= mid)
		{
			return query(l, mid, leftRootIndex, qL, qR);
		}
		else if (qL > mid)
		{
			return query(mid, r, rightRootIndex, qL, qR);
		}
		else
		{
			return merger(query(l, mid, leftRootIndex, qL, mid),
				query(mid + 1, r, rightRootIndex, mid + 1, qR));
		}
	}
public:
	ArraySegmentTree(const vector<int>& nums, function<int(int, int)> mergeFunc)
		: n(nums.size()), merger(mergeFunc) {
		// 分配 4 倍数组长度的空间，存储线段树
		tree.resize(4 * n);
		build(nums, 0, n - 1, 0);
	}

	void update(int index, int value) {
		update(0, n - 1, 0, index, value);
	}

	int query(int qL, int qR) {
		if (qL < 0 || qR >= n || qL > qR) {
			throw invalid_argument("Invalid range: [" + to_string(qL) + ", " + to_string(qR) + "]");
		}
		return query(0, n - 1, 0, qL, qR);
	}
};