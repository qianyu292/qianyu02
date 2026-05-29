//自平衡的二叉搜索树
#include<iostream>
#include<algorithm>
template<typename E>
struct AvlNode
{
	E val;
	AvlNode* left;
	AvlNode* right;
	int Height;
	AvlNode(E val) :val(val), left(nullptr), right(nullptr), Height(0) {};
};
template<typename E>
class AvlTree
{
private:
	AvlNode<E>* root;
private:
	int Height(AvlNode<E>*node)
	{
		return node ? node->Height : -1;
	}
	int balanced(AvlNode<E>* node)
	{
		return Height(node->left) - Height(node->right);
	}
	void updateHeight(AvlNode<E>* node)
	{
		if (!node)return;
		node->Height = 1 + max(Height(node->left), Height(node->right));
	}
	void MakeEmpty(AvlNode<E>*&node)
	{
		if (node==nullptr)return;
		MakeEmpty(node->left);
		MakeEmpty(node->right);
		delete node;
		node = nullptr;
	}
	// 右旋：用于LL型失衡（左子树的左孩子插入导致）
	AvlNode<E>* RotateRight(AvlNode<E>* node)
	{
		AvlNode<E>* x = node->left;
		AvlNode<E>* y = x->right;

		node->left = y;
		x->right = node;
		
		updateHeight(node);
		updateHeight(x);

		return x;
	}
	// 左旋：用于RR型失衡（右子树的右孩子插入导致）
	AvlNode<E>* RotateLeft(AvlNode<E>* node)
	{
		AvlNode<E>* x = node->right;
		AvlNode<E>* y = x->left;

		node->right = y;
		x->left = node;

		updateHeight(node);
		updateHeight(x);

		return x;
	}
	// LR型：先左旋左子树，再右旋整棵树
	AvlNode<E>* RotateLeftRight(AvlNode<E>* node)
	{
		node->left = RotateLeft(node->left);
		return RotateRight(node);
	}
	// RL型：先右旋右子树，再左旋整棵树
	AvlNode<E>* RotateRightLeft(AvlNode<E>* node)
	{
		node->right= RotateRight(node->right);
		return RotateLeft(node);
	}
	//重新平衡二叉树
	AvlNode<E>* Rebalanced(AvlNode<E>* node)
	{
		if (!node)return nullptr;

		updateHeight(node);
		int balance = balanced(node);
		if (balance > 1 && balanced(node->left) >= 0)
		{
			node=RotateRight(node);
		}
		else if(balance>1&&balanced(node->left)<0)
		{
			node=RotateLeftRight(node);
		}
		else if (balance < -1 && balanced(node->right) <= 0)
		{
			node=RotateLeft(node);
		}
		else if (balance < -1 && balanced(node->right)>0)
		{
			node=RotateRightLeft(node);
		}
		return node;
	}
	AvlNode<E>* Find(E x, AvlNode<E>* node)
	{
		if (!node)return nullptr;
		if (node->val < x)
		{
			return Find(x, node->right);
		}
		else if (node->val > x)
		{
			return Find(x, node->left);
		}
		else
		{
			return node;
		}
	}
	AvlNode<E>* FindMin(AvlNode<E>* node)
	{
		if (!node)return nullptr;
		if (!node->left)return node;
		return FindMin(node->left);
	}
	AvlNode<E>* FindMax(AvlNode<E>* node)
	{
		if (!node)return nullptr;
		if (!node->right)return node;
		return FindMax(node->right);
	}
	AvlNode<E>* Insert(E x, AvlNode<E>* node)
	{
		if (node == nullptr)
		{
			return new AvlNode<E>(x);
		}
		if (node->val < x)
		{
			node->right = Insert(x, node->right);
		}
		else if (node->val > x)
		{
			node->left = Insert(x, node->left);
		}
		else
		{
			std::cout << "已有节点" << std::endl;
			return node;
		}
		return Rebalanced(node);
	}
	AvlNode<E>* Delete(E x, AvlNode<E>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->val < x)
		{
			node->right = Delete(x,node->right);
		}
		else if (node->val > x)
		{
			node->left = Delete(x,node->left);
		}
		else
		{
			AvlNode<E>* temp = nullptr;
			if (!node->left && !node->right) {
				delete node;
				return nullptr;
			}
			else if (!node->left) {
				temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right) {
				temp = node->left;
				delete node;
				return temp;
			}
			else {
				// 双孩子情况
				AvlNode<E>* T2 = FindMin(node->right);
				node->val = T2->val;
				node->right = Delete(T2->val, node->right);
			}
		}
		updateHeight(node);

		node=Rebalanced(node);
		return node;
	}
	//返回值
public:
	AvlTree() :root(nullptr) {}
	~AvlTree()
	{
		MakeEmpty();
	}
	void MakeEmpty() { MakeEmpty(root); }
	AvlNode<E>* Find(E x) { return Find(x, root); }
	AvlNode<E>* FindMin() { return FindMin(root); }
	AvlNode<E>* FindMax() { return FindMax(root); }
	void Insert(E x) { root = Insert(x, root); }
	void Delete(E x) { root = Delete(x, root); }

	E Retrieve(AvlNode<E>* node) {
		return node->val;
	}
};