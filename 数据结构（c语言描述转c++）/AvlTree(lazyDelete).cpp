#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
template<typename T>
class LazyAvl
{
private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		int height;
		bool isDeleted;//懒惰删除标记
		int size;//有效节点计数
		int totalsize;//总结点计数
		Node(T val):data(val),left(nullptr),right(nullptr),height(0),isDeleted(false), 
		size(0),totalsize(0){}
	};
	Node* root;
	const double REBUILD_THRESHOLD = 0.5;
	int height(Node* node)
	{
		return node?node->height:0;
	}
	int getsize(Node* node)
	{
		return node ? node->size : 0;
	}
	int gettotalsize(Node* node)
	{
		return node?node->totalsize : 0;
	}
	void updateNode(Node* node)
	{
		if (!node)return;

		node->height = 1 + max(height(node->left), height(node->right));
		node->size = (node->isDeleted ? 0 : 1) + getsize(node->left) + getsize(node->right);
		node->totalsize = 1 + gettotalsize(node->left) + gettotalsize(node->right);
	}
	int getbalanced(Node* node)
	{
		return height(node->left) - height(node->right);
	}
	//右旋(LL型)
	Node* rightRotate(Node* y)
	{
		Node* x = y->left;
		Node* T2 = x->right;

		y->left = T2;
		x->right = y;

		updateNode(x);
		updateNode(y);
		return x;
	}
	//左旋(RR型)
	Node* leftRotate(Node* y)
	{
		Node* x = y->right;
		Node* T2 = x->left;

		y->right = T2;
		x->left = y;

		updateNode(x);
		updateNode(y);

		return x;
	}
	//重新平衡节点
	Node* balanced(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		int balanced = getbalanced(node);
		if (balanced > 1 && getbalanced(node->left) >= 0)
		{
			return rightRotate(node);
		}
		if (balanced > 1 && getbalanced(node->left) < 0)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		if (balanced < -1 && getbalanced(node->right) <= 0)
		{
			return leftRotate(node);
		}
		if (balanced < -1 && getbalanced(node->right)>0)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}
	bool needRebuild(Node* node)
	{
		if (!node)return false;
		return (double)(node->totalsize - node->size) / node->totalsize > REBUILD_THRESHOLD;
	}
	//重建树(物理删除所有标记节点)
	Node* rebuild(Node* node)
	{
		if (!node)return nullptr;

		vector<T> val;
		collectValid(node,val);
		return buildFromSorted(val, 0, val.size() - 1);
	}
	//收集有效节点
	void collectValid(Node* node, vector<T>& values)
	{
		if (!node)return;
		collectValid(node->left, values);
		if (!node->isDeleted)values.push_back(node->data);
		collectValid(node->right, values);
	}
	//从排序数组中构建Avl树
	Node* buildFromSorted(vector<T>& values,int start,int end)
	{
		if (start > end)return nullptr;

		int mid = start + (end - start) / 2;
		int rootval = values[mid];
		Node* root = new Node(rootval);

		root->left = buildFromSorted(values, start, mid - 1);
		root->right = buildFromSorted(values, mid + 1, end);
		updateNode(root);
		return root;
	}
	//插入节点(插入后检查懒惰删除标记再重建树)
	Node* insert(Node* node, T val)
	{
		if (!node)return new Node(val);
		
		if (val > node->data)
		{
			node->right = insert(node->right, val);
		}
		else if (val < node->data)
		{
			node->left = insert(node->left, val);
		}
		else
		{
			if (node->isDeleted)
			{
				node->isDeleted = false;
				updateNode(node);
			}
			return node;
		}
		node = balanced(node);
		if (needRebuild(node))
		{
			cout << "触发重建" << endl;
			return rebuild(node);
		}
		return node;
	}
	//懒惰删除
	Node* lazyRemove(Node* node, T val)
	{
		if (!node)return nullptr;

		if (node->data > val)
		{
			node->left = lazyRemove(node->left, val);
		}
		else if (node->data < val)
		{
			node->right = lazyRemove(node->right, val);
		}
		else
		{
			if (node->isDeleted==false)
			{
				node->isDeleted = true;
				updateNode(node);
			}
		}
		node = balanced(node);
		if (needRebuild(node))
		{
			cout << "需要重建" << endl;
			node=rebuild(node);
		}
		return node;
	}
	//查找节点
	Node* search(Node* node, T val)
	{
		if (!node)return nullptr;
		if (node->data < val)
		{
			return search(node->right, val);
		}
		else if (node->data > val)
		{
			return search(node->left, val);
		}
		else
		{
			return node->isDeleted ? nullptr : node;
		}
	}
	//中序遍历
	void inorder(Node* node, bool showDeleted = false)
	{
		if (!node)return;
		inorder(node->left, showDeleted);
		if (!node->isDeleted || showDeleted)
		{
			cout << node->data;
			if (node->isDeleted)cout << "[D]";
			cout << " ";
		}
		inorder(node->right, showDeleted);

	}
	void clear(Node*node)
	{
		if (!node)return;
		clear(node->left);
		clear(node->right);
		delete node;
	}
public:
   LazyAvl():root(nullptr){}
   ~LazyAvl() { clear(root); }
   void insert(T val)
   {
	   root = insert(root, val);
   }
   void remove(T val)
   {
	   root = lazyRemove(root, val);
   }
   bool contains(T val)
   {
	   return search(root, val) != nullptr;
   }
   void print(bool showDeleted=false)
   {
	   inorder(root, showDeleted);
	   cout << endl;
   }
   void printStats()
   {
	   cout << "有效总结点数" << getsize(root)
		   << "总结点数" << gettotalsize(root)
	       << "删除比例" << (root ? (double)(root->totalsize - root->size) / root->totalsize * 100:0)
	       << "%" << endl;
   }
   void forceRebuild()
   {
	   root = rebuild(root);
   }
};