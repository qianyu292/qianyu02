//自平衡的二叉搜索树
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

		int balance = balanced(node);
		if (balance > 1 && balanced(node->left) >= 0)
		{
			node=RotateRight(node);
		}
		if(balance>1&&balanced(node->left)<0)
		{
			node=RotateLeftRight(node);
		}
		if (balance < -1 && balanced(node->right) <= 0)
		{
			node=RotateLeft(node);
		}
		if (balance < -1 && balanced(node->right)>0)
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
		/*
	* Insert思路：
	* 1. 递归终止条件：如果当前节点为空，在此位置创建新节点并返回
	*   
	*
	* 2. 递归插入：
	*    - 如果 x < node->val，递归插入左子树
	*    - 如果 x > node->val，递归插入右子树：
	*    - 如果 x == node->val，根据需求决定：直接返回node（不允许重复）或插入右子树
	*
	* 3. 更新高度：
	*    updateHeight(node);  
	*
	* 4. 平衡调整：
	*    
	*
	* 5. 返回当前子树的新根节点
	*    
	*
	* 注意：由于插入只会让树高度增加1，最多只需一次旋转即可恢复平衡
	*/
	}
	AvlNode<E>* Delete(E x, AvlNode<E>* node)
	{
		/*
	 * Delete思路：
	 * 1. 递归终止条件：如果当前节点为空，说明没找到，直接返回nullptr
	 *    
	 *
	 * 2. 查找要删除的节点：
	 *    - 如果 x < node->val，去左子树删除：
	 *    - 如果 x > node->val，去右子树删除：
	 *    - 如果 x == node->val，找到目标，执行删除操作（见步骤3）
	 *
	 * 3. 删除节点的三种情况：
	 *    【情况A：叶子节点（左右都为空）】
	 *      直接删除：
	 *
	 *    【情况B：只有一个子节点】
	 *      用子节点替换当前节点：
	 *      
	 *
	 *    【情况C：有两个子节点】
	 *      方案（用后继节点替换）：
	 *        - 找到右子树的最小节点：
	 *        - 将minNode的值复制到当前节点：
	 *        - 递归删除右子树中的minNode：
	 *  
	 *
	 * 4. 如果节点被删除了（node变为nullptr），直接返回nullptr
	 *    
	 *
	 * 5. 更新高度：
	 *   
	 *
	 * 6. 平衡调整：
	 *  
	 *    （注意：删除可能导致多次旋转，因为删除可能让树高度减少，影响祖先节点的平衡）
	 *
	 * 7. 返回当前子树的新根节点
	 *    return node;
	 */
	}
	//返回值
public:
	AvlTree() :root(nullptr) {}
	~AvlTree()
	{
		MakeEmpty();
	}
	AvlNode<E>* Find(E x) { return Find(x, root); }
	AvlNode<E>* FindMin() { return FindMin(root); }
	AvlNode<E>* FindMax() { return FindMax(root); }
	void Insert(E x) { root = Insert(x, root); }
	void Delete(E x) { root = Delete(x, root); }

	E Retrieve(AvlNode<E>* node) {
		return node->val;
	}
};