#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class BinomialQueue {
private:
    struct BinomialNode {
        T element;
        BinomialNode* leftChild;
        BinomialNode* nextSibling;

        explicit BinomialNode(const T& e, BinomialNode* lt = nullptr, BinomialNode* rt = nullptr)
            : element(e), leftChild(lt), nextSibling(rt) {
        }
    };

    std::vector<BinomialNode*> trees;  // 存储各阶二项树的根节点
    int currentSize;

    // 合并两棵同阶二项树，返回新树根（t1的根值更小）
    BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2) {
        if (t2->element < t1->element) {
            std::swap(t1, t2);
        }
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        return t1;
    }

    // 获取二项树的阶数（节点数 = 2^k）
    int findOrder(BinomialNode* t) const {
        if (!t) return -1;
        int order = 0;
        BinomialNode* child = t->leftChild;
        while (child) {
            ++order;
            child = child->nextSibling;
        }
        return order;
    }

    // 删除整棵二项树
    void deleteTree(BinomialNode* t) {
        if (!t) return;
        deleteTree(t->leftChild);
        deleteTree(t->nextSibling);
        delete t;
    }

public:
    BinomialQueue() : currentSize(0) {}

    ~BinomialQueue() {
        clear();
    }

    // 插入元素
    void insert(const T& x) {
        BinomialQueue tmp;
        tmp.trees.resize(1);
        tmp.trees[0] = new BinomialNode(x);
        tmp.currentSize = 1;
        merge(tmp);
        // tmp 的 trees 在 merge 中被置空，不会 double delete
    }

    // 查找最小值
    const T& findMin() const {
        if (currentSize == 0) {
            throw std::underflow_error("BinomialQueue is empty");
        }
        int minIndex = -1;
        for (size_t i = 0; i < trees.size(); ++i) {
            if (trees[i]) {
                if (minIndex == -1 || trees[i]->element < trees[minIndex]->element) {
                    minIndex = i;
                }
            }
        }
        return trees[minIndex]->element;
    }

    // 删除最小值
    void deleteMin() {
        if (currentSize == 0) {
            throw std::underflow_error("BinomialQueue is empty");
        }

        // 1. 找到最小根所在的树索引
        int minIndex = -1;
        T minValue;
        for (size_t i = 0; i < trees.size(); ++i) {
            if (trees[i]) {
                if (minIndex == -1 || trees[i]->element < minValue) {
                    minValue = trees[i]->element;
                    minIndex = i;
                }
            }
        }

        // 2. 移除该树，并将其子树分离为新的二项队列
        BinomialNode* oldRoot = trees[minIndex];
        BinomialNode* deletedTree = oldRoot->leftChild;
        delete oldRoot;

        // 3. 构建一个临时的二项队列（由子树组成）
        BinomialQueue deletedQueue;
        int childCount = minIndex;  // 子树的阶数为 0,1,...,minIndex-1
        deletedQueue.trees.resize(childCount, nullptr);
        deletedQueue.currentSize = (1 << minIndex) - 1;

        BinomialNode* child = deletedTree;
        for (int j = childCount - 1; j >= 0; --j) {
            deletedQueue.trees[j] = child;
            child = child->nextSibling;
            deletedQueue.trees[j]->nextSibling = nullptr;
        }

        trees[minIndex] = nullptr;
        currentSize -= (1 << minIndex);

        // 4. 合并
        merge(deletedQueue);
    }

    // 合并两个二项队列
    void merge(BinomialQueue& rhs) {
        if (this == &rhs) return;

        currentSize += rhs.currentSize;
        rhs.currentSize = 0;

        size_t newSize = std::max(trees.size(), rhs.trees.size()) + 1;
        std::vector<BinomialNode*> newTrees(newSize, nullptr);

        BinomialNode* carry = nullptr;
        for (size_t i = 0; i < newSize; ++i) {
            BinomialNode* t1 = (i < trees.size()) ? trees[i] : nullptr;
            BinomialNode* t2 = (i < rhs.trees.size()) ? rhs.trees[i] : nullptr;

            // 统计当前位置上有多少棵树（最多3棵：t1, t2, carry）
            int sum = (t1 ? 1 : 0) + (t2 ? 1 : 0) + (carry ? 1 : 0);

            switch (sum) {
            case 0:  // 无树
                break;
            case 1:  // 只有一棵树，直接放入
                if (t1) newTrees[i] = t1;
                else if (t2) newTrees[i] = t2;
                else newTrees[i] = carry;
                carry = nullptr;
                break;
            case 2:  // 两棵树，合并后进位
                if (t1 && t2) {
                    carry = combineTrees(t1, t2);
                }
                else if (t1 && carry) {
                    carry = combineTrees(t1, carry);
                }
                else {  // t2 && carry
                    carry = combineTrees(t2, carry);
                }
                break;
            case 3:  // 三棵树，留一棵，合并另外两棵进位
                newTrees[i] = carry;
                carry = combineTrees(t1, t2);
                break;
            }
        }

        trees = std::move(newTrees);
        rhs.trees.clear();
    }

    // 判断是否为空
    bool isEmpty() const {
        return currentSize == 0;
    }

    // 获取元素个数
    int size() const {
        return currentSize;
    }

    // 清空队列
    void clear() {
        for (BinomialNode* root : trees) {
            deleteTree(root);
        }
        trees.clear();
        currentSize = 0;
    }
};