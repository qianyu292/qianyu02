#include<vector>
#include<stack>
#include<algorithm>
#include<iostream>
//用栈模拟实现非递归插入AvlTree
struct AvlNode
{
	int key;
	int height;
	AvlNode* left;
	AvlNode* right;
	AvlNode(int k) :key(k), height(0), left(nullptr),right(nullptr){}
};
class AvlTree
{
private:
	AvlNode* root;
	//获取节点高度
	int getHeight(AvlNode* node)
	{
		return node == nullptr ? 0 : node->height;
	}
	//更新节点高度
	void updateHeight(AvlNode* node)
	{
		if (node != nullptr)
		{
			node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
		}
	}
	//获取平衡因子
	int getBalanceFactor(AvlNode* node)
	{
		if (node == nullptr)return 0;
		return getHeight(node->left) - getHeight(node->right);
	}
	//右旋操作
	AvlNode* rightRotate(AvlNode* y)
	{
		AvlNode* x = y->left;
		AvlNode* T2 = x->right;

		x->right = y;
		y->left = T2;

		updateHeight(x);
		updateHeight(y);

		return x;
	}
	//左旋操作
	AvlNode* leftRotate(AvlNode*y)
	{
		AvlNode* x = y->right;
		AvlNode* T2 = x->left;

		x->left = y;
		y->right = T2;

		updateHeight(x);
		updateHeight(y);
		
		return x;
	}
	//重新平衡
	AvlNode* rebalance(AvlNode* node)
	{
		updateHeight(node);
		int balance = getBalanceFactor(node);
		if (balance > 1 && getBalanceFactor(node->left) >= 0)
		{
			return rightRotate(node);
		}
		if (balance > 1 && getBalanceFactor(node->left) < 0)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		if (balance < -1 && getBalanceFactor(node->right) >= 0)
		{
			return leftRotate(node);
		}
		if (balance < -1&& getBalanceFactor(node->right) < 0)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}
public:
	AvlTree():root(nullptr){}
	//非递归插入
	void insert(int key)
	{
		if (root == nullptr)
		{
			root = new AvlNode(key);
			return;
		}
		std::stack<AvlNode*>path;
		AvlNode* current = root;
		while (current != nullptr)
		{
			path.push(current);
			if (key < current->key)
			{
				if (current->left == nullptr)
				{
					current->left = new AvlNode(key);
					break;
				}
				current = current->left;
			}
			else if (key > current->key)
			{
				if (current->right == nullptr)
				{
					current->right = new AvlNode(key);
				}
				current = current->right;
			}
			else
			{
				return;
			}
		}
		while (!path.empty())
		{
			AvlNode* node = path.top();
			path.pop();

			AvlNode* balanced = rebalance(node);
			if (!path.empty())
			{
				AvlNode* parent = path.top();
				if (parent->left == node)
				{
					parent->left = balanced;
				}
				else
				{
					parent->right = balanced;
				}
			}
			else
			{
				root = balanced;
			}
		}
	}
	void inorderTraversal(AvlNode* node)
	{
		if (node == nullptr)
		{
			return;
		}
		inorderTraversal(node->left);
		std::cout << node->key << "(h:" << node->height << ")";
		inorderTraversal(node->right);
	}
	void printTree()
	{
		inorderTraversal(root);
		std::cout << std::endl;
	}
	//检查是否为平衡树
	bool isBalance(AvlNode* node)
	{
		if (node == nullptr)return true;
		int balance = getBalanceFactor(node);
		if (abs(balance) > 1)return false;

		return isBalance(node->left) && isBalance(node->right);
	}
	bool checkBalanced()
	{
		return isBalance(root);
	}
};