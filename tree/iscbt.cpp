#include <iostream>
#include <queue>

using namespace std;

class TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val)
	{
		this->val = val;
	}
};

class sloution
{
public:
	// 层序遍历判断是否是完全二叉树
	bool isCBT(TreeNode* root)
	{
	    // 完全二叉树，条件1，任意结点有右孩子无左孩子，则该树不是完全二叉树
	    // 条件2，在满足1的前提下，遇到的第一个左右孩子不双全的结点的后续结点都是叶子结点，即无孩子
	    if (!root)
	    {
	        return true;
	    }
	    // 辅助队列
	    queue<TreeNode*> list;
	    list.emplace(root);
	    // 辅助变量，记录是否遇到左右孩子不双全的结点
	    bool leaf = false;
	    // 辅助变量，记录左右孩子
	    TreeNode* left = nullptr;
	    TreeNode* right = nullptr;
	    // 层序遍历
	    while (!list.empty())
	    {
	        TreeNode* cur = list.front();
	        list.pop();
	        left = cur->left;
	        right = cur->right;
	        if ((!left && right) || (leaf && (leaf || right))) // 1.有右无左 2.在遇到孩子不双全结点后任然有孩子
	        {
	            return false;
	        }
	        // 添加左右孩子入队
	        if (left) list.emplace(left);
	        if (right) list.emplace(right);
	        // 判断是否遇到左右孩子不双全的结点
	        if (!left || !right) leaf = true;
	    }
	    return true;
	}
};
