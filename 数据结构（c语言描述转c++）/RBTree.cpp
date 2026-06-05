//手写红黑树
#include<cassert>
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;
enum Color { RED, BLACK };
template<typename T>
struct RBNode
{
	T key;
	Color color;
	int height;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	RBNode(T k, Color c = RED) :key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};
template<typename T>
class RedBlackTree
{
private:
	RBNode<T>* root;
	RBNode<T>* NIL;//哨兵节点，表示空节点
	void InitNIL()
	{
		NIL = new RBNode<T>(T(), BLACK);
		NIL->left = NIL;
		NIL->right = NIL;
		NIL->parent = nullptr;
		root = NIL;
	}
	int Height(RBNode<T>* node)
	{
		return node?node->height:-1;
	}
	void updateHeight(RBNode<T>* node)
	{
		if (!node)return;
		node->height = 1 + max(Height(node->left), Height(node->right));
	}
	//左旋
	void leftRotate(RBNode<T>* x)
	{
		RBNode<T>* y = x->right;
		x->right = y->left;
		if (y->left != NIL)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr)
		{
			root = y;
		}
		else if (x->parent->left == x)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
		updateHeight(x);
		updateHeight(y);
	}
	//右旋
	void rightRotate(RBNode<T>* x)
	{
		RBNode<T>* y = x->left;
		x->left = y->right;
		if (y->right != NIL)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr)
		{
			root = y;
		}
		else if (x->parent->left == x)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
		updateHeight(x);
		updateHeight(y);
	}
	//插入修复
	void InsertFixup(RBNode<T>* z)
	{
		/*思路：插入节点默认是红色，只会违反不红红或根叶黑
		* 如果违反了根叶黑则是根节点直接变黑
		* 违反不红红(插入节点和父亲节点都是红色)：看叔叔节点颜色
		* case1:如果叔叔是红色：叔父爷变色，再将插入节点修复判断跳到爷爷进行递归修复
		* case2:如果叔叔是黑色：要根据LL，RR，LR，RL进行旋转，再对旋转中心点和被旋转点进行变色
		* 同时可以用对称来简化思路和实现
		*/
		while (z->parent != NIL && z->parent->color==RED)
		{
			RBNode<T>* x = z->parent, y = z->parent->parent;
			if (y!=NIL&&y->left==x)
			{
				if (y->right!=NIL&&y->right->color == RED)
				{
					x->color = BLACK;
					y->color = RED;
					y->right->color = BLACK;
					z = y;
				}
				else if (y->right->color == BLACK)
				{
					if (x->left == z)
					{
						rightRotate(y);
						y->color = RED;
						x->color = BLACK;
						z = x;
					}
					else if(x->right==z)
					{
						leftRotate(x);
						rightRotate(y);
						y->color = RED;
						z->color = BLACK;
						z = z->parent;
					}
				}
			}
			else
			{
				if (y != NIL && y->right == x)
				{
					if (y->left!=NIL&&y->left->color == RED)
					{
						y->color = RED;
						x->color = BLACK;
						y->left->color = BLACK;
						z = y;
					}
					else if (y->left->color == BLACK)
					{
						if (x->right == z)
						{
							leftRotate(y);
							y->color = RED;
							x->color = BLACK;
							z = x;
						}
						else
						{
							rightRotate(x);
							leftRotate(y);
							y->color = RED;
							z->color = BLACK;
							z = z->parent;
						}
					}
				}
			}
		}
		root->color = BLACK;
	}
	//删除最小节点的辅助函数:用v替换u
	void transplant(RBNode<T>* u, RBNode<T>* v)
	{
		if (u->parent == nullptr)
		{
			root = v;
		}
		else if (u->parent->left == u)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}
	//查找最小节点
	RBNode<T>* minimum(RBNode<T>* node)
	{
		if (node == NIL)return nullptr;
		if (node->left == NIL)return node;
		return minimum(node->left);
	}
	//删除修复
	void deleteFixup(RBNode<T>* x)
	{
		/*思路:先按AVL看节点
		*1.既有左孩子又有右孩子:找到右子树的最小值代替该节点， 再递归删除
		*2.只有左孩子/右孩子:让孩子代替过来，并变色
		*3.没有左孩子和右孩子:
		*一.若删除的是红节点，直接删除即可
		*二.若删除的是黑节点:给删除节点加一个双黑标记,双黑节点视为少一个黑色
		* (1)兄弟是黑色：[1]兄弟至少有一个红孩子if（LL，RR型子变父的颜色，父变爷的颜色，爷变黑，再按需旋转）
		*                                       else if(LR，RL型子变爷的颜色，爷再变黑，再按需旋转)
		*                [2]兄弟孩子全是黑色：兄弟变红，双黑上移:if(为黑):再递归进行删除修复else if（红节点）直接变单黑
		* (2)兄弟是红色：兄父变色，朝双黑旋转（保持双黑继续修复）
		*/
		while (x != root && x->color == BLACK)
		{
			RBNode<T>* y = x->parent;
			if (y->left == x)
			{
				RBNode<T>* z = y->right;
				if (z->color == RED)
				{
					z->color = BLACK;
					y->color = RED;
					leftRotate(y);
					z = y->right;
				}
				else if (z->color == BLACK)
				{
					if (z->left->color == BLACK && z->right->color == BLACK)
					{
						z->color = RED;
						x = y;
						if (x->color == RED)
						{
							x->color = BLACK;
						}
					}
					else
					{
						if (z->right->color == BLACK)
						{
							z->left->color = BLACK;
							z->color = RED;
							rightRotate(z);
							z = x->parent->right;
						}
						z->right->color = z->color;
						z->color = y->color;
						y->color = BLACK;
						leftRotate(y);
						x = z;
					}
				}
			}
			else if(y->right==x)
			{
				RBNode<T>* z = y->left;
				if (z->color == RED)
				{
					z->color = BLACK;
					y->color = RED;
					rightRotate(y);
					z = y->left;
				}
				else if (z->color == BLACK)
				{
					if (z->left->color == BLACK && z->right->color == BLACK)
					{
						z->color = RED;
						x = y;
						if (x->color == RED)
						{
							x->color = BLACK;
						}
					}
					else
					{
						if (z->left->color == BLACK)
						{
							z->left->color = BLACK;
							z->color = RED;
							leftRotate(z);
							z = x->parent->left;
						}
						z->left->color = z->color;
						z->color = y->color;
						y->color = BLACK;
						rightRotate(y);
						x = z;
					}
				}
			}
		}
		x->color = BLACK;
	}
	void destroyTree(RBNode<T>* node)
	{
		if (node != NIL)
		{
			destroyTree(node->left);
			destroyTree(node->right);
			delete node;
			node = nullptr;
		}
	}
	void printTree(RBNode<T>* node, int level, string prefix)
	{
		if (node != NIL)
		{
			printTree(node->right, level + 1, "/");

			for (int i = 0; i < level; ++i)cout << "   ";
			cout << prefix << node->key << "(" << (node->color == RED ? "R" : "B") << ")" << endl;

			printTree(node->left, level + 1, "\\");
		}
	}
	bool varifyProperties(RBNode<T>* node, int blackcount, int& pathBlackHeight)
	{
		if (node == NIL)//如果节点为叶子节点
		{
			if (pathBlackHeight == -1)//看是否符合黑路同
			{
				pathBlackHeight = blackcount;
				return true;
			}
			else if (blackcount != pathBlackHeight)//看是否符合黑路同
			{
				return false;
			}
		}
		if (node->color == RED)//如果节点为红色
		{
			if (node->left != NIL && node->left->color == RED)//看是否违反不红红
			{
				return false;
			}
			if (node->right != NIL && node->right->color == RED)
			{
				return false;
			}
		}
		if (node->color == BLACK)
		{
			blackcount++;//节点黑色
		}
		return varifyProperties(node->left, blackcount, pathBlackHeight) &&
			varifyProperties(node->right, blackcount, pathBlackHeight);
	}
public:
	RedBlackTree() {InitNIL(); }
	~RedBlackTree()
	{
		destroyTree(root);
	}

	void Insert(T key)
	{
		RBNode<T>* z = new RBNode<T>(key, RED);
		z->left = z->right = NIL;
		RBNode<T>* y = NIL;//y是要插入的点的父亲
		RBNode<T>* x = root;
		while (x != NIL)//找到插入点的父亲
		{
			y = x;
			if (x->key < key)
			{
				x = x->right;
			}
			else if (x->key > key)
			{
				x = x->left;
			}
			else
			{
				delete z;
				return;
			}
		}
		z->parent = y;
		if(y==NIL)
		{
			root = z;
		}
		if (y->key > z->key)
		{
			y->left = z;
		}
		else if (y->key < z->key)
		{
			y->right = z;
		}
		if (z->parent == NIL)
		{
			z->color = BLACK;
			return;
		}
		InsertFixup(z);
	}
	
	void remove(T key)
	{
		RBNode<T>* z = search(key);
		if (z == NIL)return;

		RBNode<T>* y = z;//y指向实际要删除的节点
		RBNode<T>* x;//节点x指向替换y的节点
		Color y_original_color = y->color;//记录y的原始颜色
		if (z->left == NIL)
		{
			x = z->right;
			transplant(z, z->right);
			if (z->color == BLACK)
			{
				x->color = BLACK;
			}
			
		}
		else if (z->right == NIL)
		{
			x = z->left;
			transplant(z, z->left);
			if (z->color == BLACK)
			{
				x->color = BLACK;
			}
		}
		else
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				transplant(y, y->right);//用y的右子节点替换y
				y->right = z->right;//让y接替z的右子树
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;//让y接替z的右子树
			y->left->parent = y;
			y->color = z->color;//y继承z的颜色
		}
		delete z;
		if (y_original_color == BLACK)
		{
			deleteFixup(x);
		}
	}
	RBNode<T>* search(T key)
	{
		if (root == NIL)return nullptr;
		RBNode<T>* x = root;
		while (x!=NIL&&x->key != key)
		{
			if (x->key < key)
			{
				x = x->right;
			}
			else if(x->key > key)
			{
				x = x->left;
			}
		}
		if (x == NIL)return NIL;
		return x;
	}
	void levelOrder()
	{
		if (root == NIL)return;
		queue<RBNode<T>*>q;
		q.push(root);
		int level = 0;
		while (!q.empty())
		{
			int sz = q.size();
			cout << "this is" << level << "level" << endl;
			for (int i = 0; i < sz; ++i)
			{
				RBNode<T>* node = q.front();
				q.pop();
				cout << node->key << " " << (node->color == RED ? "R" : "B");
				if (node->left != NIL)
				{
					q.push(node->left);
				}
				if (node->right != NIL)
				{
					q.push(node->right);
				}
			}
			cout << endl;
			level++;
		}
	}
	void print()
	{
		return printTree(root, 0, "");
	}
	//验证红黑树性质
	bool varify()
	{

		if (root == NIL)return true;

		if (root->color != BLACK)
		{
			cout << "Root is BLACK" << endl;
			return false;
		}
		int blackHeight = -1;
		return varifyProperties(root, 0, blackHeight);
	}
};