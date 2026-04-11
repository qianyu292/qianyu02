#include<vector>
//二叉树节点
template<typename E>
struct TreeNode
{
	E val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : left(nullptr), right(nullptr) {}
	TreeNode(E x) : val(x), left(nullptr), right(nullptr) {}
};
void traverse(TreeNode<int>* root)
{
	if (root == nullptr)
	{
		return;
	}
	//前序遍历位置
	traverse(root->left);
	//中序遍历位置
	traverse(root->right);
	//后序遍历位置
}
//多叉树节点
template<typename E>
struct treeNode
{
	E val;
	std::vector<treeNode*>children;
};
void traverse2(treeNode<int>* root)
{
	if (root == nullptr)
	{
		return;
	}
	//前序遍历位置
	for (treeNode<int>* child : root->children)
	{
		traverse2(child);
	}
	//后序遍历位置
 }
//二叉搜索树：左子树节点一定比根节点小，右子树节点一定比根节点大。
template<typename E>
class SearchTree
{
private:
	TreeNode<E>* root;
public:
	SearchTree():root(nullptr){}
	~SearchTree()
	{
		MakeEmpty(root);
	}
	TreeNode<E>* MakeEmpty(TreeNode<E>*root)
	{
		if (root != nullptr)
		{
			MakeEmpty(root->left);
			MakeEmpty(root->right);
			delete root;
		}
		return nullptr;
	}
	TreeNode<E>* Find(E x, TreeNode<E>*root)
	{
		if (root == nullptr)
		{
			return nullptr;
	   }
		if (x < root->val)
		{
			return Find(x, root->left);
		}
		else if (x > root->val)
		{
			return Find(x, root->right);
		}
		else
		{
			return root;
		}
	}
	TreeNode<E>* FindMin(TreeNode<E>*root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (root->left == nullptr)
		{
			return root;
		}
		else
		{
			return FindMin(root->left);
		}
	}
	TreeNode<E>* FindMax(TreeNode<E>* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (root->right == nullptr)
		{
			return root;
		}
		else
		{
			return FindMax(root->right);
		}
	}
	TreeNode<E>* Insert(E x,TreeNode<E>*root)
	{
		if (root == nullptr)
		{
			root = new TreeNode<E>(x);
		}
		else if (x < root->val)
		{
			root->left = Insert(x,root->left);
		}
		else if (x > root->val)
		{
			root->right = Insert(x,root->right);
		}
		return root;
	}
	TreeNode<E>* Delete(E x,TreeNode<E>*root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		if (x < root->val)
		{
			root->left = Delete(x, root->left);
		}
		else if (x > root->val)
		{
			root->right = Delete(x, root->right);
		}
		else
		{
			if (root->left && root->right)
			{
				TreeNode<E>* T = FindMin(root->right);
				root->val = T->val;
				root->right = Delete(T->val, root->right);
			}
			else
			{
				TreeNode<E>* temp = root;
				if (!root->left)
				{
					root = root->right;
				}
				else
				{
					root = root->left;
				}
				delete temp;
			}
		}
		return root;
	}
	E Retrieve(TreeNode<E>* p)
	{
		return p->val;
	}
};