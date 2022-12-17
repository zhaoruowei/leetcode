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
	// 树型DP判断是否是二叉搜索树
    // 左子树最大值 < 当前子树值 < 右子树最小值
    bool isBSTDP(TreeNode* root)
    {
        ReturnType* ans = isBSTDPprocess(root);
        return ans->isB;
    }
private:
    // 树型DP递归返回信息结构体
    struct ReturnType
    {
        bool isB; // 返回当前子树是否是二叉搜索树
        int min; // 当前子树的最小值
        int max; // 当前子树的最大值
        ReturnType (bool is, int mi, int ma) // 构造函数
        {
            this->isB = is;
            this->min = mi;
            this->max = ma;
        }
    };
    // 树型DP递归函数
    ReturnType* isBSTDPprocess(TreeNode* root)
    {
        // 终止条件，遇到nullptr节点的返回值
        if (!root)
        {
            return nullptr;
        }
        // 接受左子树返回信息
        ReturnType* leftData = isBSTDPprocess(root->left);
        // 接受右子树返回信息
        ReturnType* rightData = isBSTDPprocess(root->right);
        // 加工当前子树的返回信息
        int min = root->val, max = root->val;
        bool isB = true;
        // 当前子树的最大最小值等于整颗子树的最大最小值
        if (leftData) // 左子树不为空
        {
            min = min < leftData->min ? min : leftData->min;
            max = max > leftData->max ? max : leftData->max;
        }
        if (rightData) // 右子树不为空
        {
            min = min < rightData->min ? min : rightData->min;
            max = max > rightData->max ? max : rightData->max;
        }
        // 1.左右子树任一子树不是二叉搜索树，不满足
        // 2.当前子树不大于左子树最大值，或不小于右子树最小值
        if (leftData && (!leftData->isB || root->val <= leftData->max)) // 左子树不为空时，左子树不是二叉搜索树，或者当前值不大于左子树最大值
        {
            isB = false;
        }
        if (rightData && (!rightData->isB || root->val >= rightData->min)) // 右子树不为空时，右子树不是二叉搜索树，或者当前值不小于右子树最小值
        {
            isB = false;
        }
        
        delete leftData;
        delete rightData;
        
        // 返回当前子树信息
        return new ReturnType(isB, min, max);
    }
};
