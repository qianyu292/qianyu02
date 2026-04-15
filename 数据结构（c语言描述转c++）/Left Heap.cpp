//左式堆实现merge操作
//回来再自己独立实现
#include<stdexcept>
#include<utility>
#include<functional>
template<typename E,typename Compare=std::less<E>>
struct TreeNode
{
	E val;
	TreeNode* left;
	TreeNode* right;
	int Npl;
	TreeNode(const E& e) :val(e), left(nullptr), right(nullptr), Npl(0) {};
};
template<typename E, typename Compare = std::less<E>>
class LeftistHeap
{
private:
	TreeNode<E,Compare>* root;
	Compare cmp;
	void swapChildren(TreeNode<E, Compare>* t)
	{
		TreeNode<E, Compare>* temp = t->left;
		t->left = t->right;
		t->right = temp;
	}
	TreeNode<E, Compare>* merge(TreeNode<E, Compare>* h1, TreeNode<E, Compare>* h2)
	{
		if (h1 == nullptr)return h2;
		if (h2 == nullptr)return h1;
		if (cmp(h2->val, h1->val))
		{
			std::swap(h1,h2);
		}
		h1->right=merge(h1->right,h2);
		int leftNpl=(h1->left!=nullptr)?h1->left->Npl:-1;
		int rightNpl=(h1->right!=nullptr)?h1->right->Npl:-1;
		if (rightNpl > leftNpl)
		{
			swapChildren(h1);
		}
		int minChildNpl = (h1->right != nullptr) ? h1->right->Npl : -1;
		h1->Npl = minChildNpl + 1;

		return h1;
	}
	TreeNode<E, Compare>* insert1(const E& x, TreeNode<E, Compare>* h)
	{
		TreeNode<E, Compare>* newnode = new TreeNode<E, Compare>(x);
		return merge(h, newnode);
	}
	TreeNode<E, Compare>* deleteMin1(TreeNode<E, Compare>* h1)
	{
		if (h1 == nullptr)
		{
			throw std::runtime_error("Left Heap is Empty");
		}
		TreeNode<E, Compare>* left = h1->left;
		TreeNode<E, Compare>* right = h1->right;
		delete h1;
		return merge(left, right);
	}
	TreeNode<E, Compare>* clone(TreeNode<E, Compare>* t)const
	{
		if (t == nullptr)return nullptr;
		TreeNode<E, Compare>* newnode = new TreeNode<E, Compare>(t->val);
		newnode->left = clone(t->left);
		newnode->right = clone(t->right);
		newnode->Npl = t->Npl;
		return newnode;
	}
	void MakeEmpty(const TreeNode<E, Compare>* t)
	{
		if(t != nullptr)
		{
			MakeEmpty(t->left);
			MakeEmpty(t->right);
			delete t;
			t = nullptr;
		}
	}
	size_t size(TreeNode<E, Compare>* t)const
	{
		if (t == nullptr)return 0;

		return 1 + size(t->left) + size(t->right);
	}
public:
	LeftistHeap() :root(nullptr) {};
	~LeftistHeap()
	{
		MakeEmpty(root);
	}
	bool isEmpty()const
	{
		return root == nullptr;
	}
	const E& FindMin()const
	{
		if (isEmpty())
		{
			throw "Left Heap is Empty";
		}
		return root->val;
	}
	void insert(const E& x)
	{
		root = insert1(x, root);
	}
	void deleteMin()
	{
		root = deleteMin1(root);
	}
	void merge(LeftistHeap& other)
	{
		if (this == &other)return;
		root = merge(root, other.root);
		other.root = nullptr;
	}
	size_t size()const
	{
		return size(root);
	}
};