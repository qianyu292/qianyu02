//自平衡的二叉搜索树
//没太懂，学完回来重做
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
public:
	AvlTree()
	{
		root = nullptr;
	}
	~AvlTree()
	{
		MakeEmpty(root);
	}
	int Height(AvlNode<E>*node)
	{
		return node == nullptr ? 0 : node->Height;
	}
	void updateHeight(AvlNode<E>* node)
	{
		if (node)
		{
			int leftHeight = Height(node->left);
			int rightHeight = Height(node->right);
			node->Height = (rightHeight > leftHeight ? rightHeight : leftHeight) + 1;
		}
	}
	void MakeEmpty(AvlNode<E>*node)
	{
		if (node)
		{
			MakeEmpty(node->left);
			MakeEmpty(node->right);
			delete node;
		}
	}
	AvlNode<E>* Find(E x, AvlNode<E>*node)
	{
		if (node == nullptr) 
		{
			return nullptr;
		}
		if (node->val == x)
		{
			return node;
		}
		else if (node->val > x)
		{
			return Find(x, node->left);
		}
		else if (node->val < x)
		{
			return Find(x, node->right);
		}
	}
	AvlNode<E>* FindMin(AvlNode<E>*node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->left == nullptr)
		{
			return node;
		}
		else
		{
			return FindMin(node->left);
		}
	}
	AvlNode<E>*FindMax(AvlNode<E>*node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->right == nullptr)
		{
			return node;
		}
		else
		{
			return FindMax(node->right);
		}
	}
	AvlNode<E>* Insert(E x, AvlNode<E>*node)
	{
		if (node == nullptr)
		{
			return new AvlNode<E>(x);
		}
		else if (node->val < x)
		{
			node->right = Insert(x, node->right);
			if (Height(node->right) - Height(node->left) == 2)
			{
				if (x > node->right->val)
				{
					node=SingleRotateWithright(node);
				}
				else
				{
					node=DoubleRotateWithRight(node);
				}
			}
		}
		else if (node->val > x)
		{
			node->left = Insert(x, node->left);
			if (Height(node->left) - Height(node->right) == 2)
			{
				if (x < node->left->val)
				{
					node=SingleRotateWithLeft(node);
				}
				else
				{
					node=DoubleRotateWithLeft(node);
				}
			}
		}
		updateHeight(node);
		return node;
	}
	AvlNode<E>* Delete(E x, AvlNode<E>*node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->val > x)
		{
			node->left=Delete(x, node->left);
		}
		else if (node->val < x)
		{
			node->right=Delete(x, node->right);
		}
		else
		{
			if (node->left && node->right)
			{
				AvlNode<E>* p = FindMin(node->right);
				node->val = p->val;
				node->right = Delete(p->val, node->right);
			}
			else
			{
				AvlNode<E>* temp = node;
				if (node->left == nullptr)
				{
					node = node->right;
				}
				else if (node->right == nullptr)
				{
					node = node->left;
				}
				delete temp;
			}
		}
		if (node == nullptr)return nullptr;

		updateHeight(node);

		int balance = Height(node->left) - Height(node->right);

		if (balance > 1)
		{
			if (Height(node->left->left) >= Height(node->left->right))
			{
				return  SingleRotateWithLeft(node);
			}
			else
			{
				return DoubleRotateWithLeft(node);
			}
		}
		if (balance < -1)
		{
			if (Height(node->right->right) >= Height(node->right->left))
			{
				return SingleRotateWithRight(node);
			}
			else
			{
				return DoubleRotateWithRight(node);
			}
		}
		return node;
	}
	E Retrieve(AvlNode<E>* node)
	{
		return node->val;
	}
	AvlNode<E>* SingleRotateWithLeft(AvlNode<E>* node)
	{
		AvlNode<E>* p = node->left;
		node->left = p->right;
		p->right = node;
		updateHeight(node);
		updateHeight(p);
		return p;
	}
	AvlNode<E>* SingleRotateWithRight(AvlNode<E>* node)
	{
		AvlNode<E>* p = node->right;
		node->right = p->left;
		p->left = node;
		updateHeight(node);
		updateHeight(p);
		return p;
	}
	AvlNode<E>* DoubleRotateWithLeft(AvlNode<E>* node)
	{
		node->left = SingleRotateWithRight(node->left);

		return SingleRotateWithLeft(node);
	}
	AvlNode<E>* DoubleRotateWithRight(AvlNode<E>* node)
	{
		node->right = SingleRotateWithLeft(node->right);

		return SingleRotateWithRight(node);
	}
};