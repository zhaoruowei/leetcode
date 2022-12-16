#include <iostream>
#include <climits>

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
	int preval = INT_MIN;
public:
	bool isBST(TreeNode* root)
	{
		if (!root)
		{
			return true;
		}
		bool isLeft = isBST(root->left);
		if (isLeft)
		{
			if (root->val <= preval) return false;
			else preval = root->val;
		}
		else return false;
		return isBST(root->right);
	}
		// 中序迭代遍历判断是否二叉搜索树
	bool isBSTIteration(TreeNode* root)
	{
	    // 辅助栈，用于中序迭代遍历
	    stack<TreeNode*> list;
	    // 遍历二叉树
	    while (!list.empty() || root)
	    {
	        if (root)
	        {
	            list.emplace(root);
	            root = root->left;
	        }
	        else
	        {
	            root = list.top();
	            list.pop();
	            // 检查当前结点
	            if (root->val <= preval) return false;
	            else preval = root->val;
	            root = root->right;
	        }
	    }
	    return true;
	}
};
