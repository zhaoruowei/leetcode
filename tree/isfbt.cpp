#include <iostream>
#include <cmath>

using namespace std;

class TreeNode
{
public:
	int val;
	TreeNode* left;
	TreeNode* right;
public:
	TreeNode (int val)
	{
		this->val = val;
		this->left = nullptr;
		this->right = nullptr;
	}
};


class Traversal
{
public:
	// 判断是否是满二叉树，二叉树的深度为d，结点个数为n
	// 满二叉树满足2^d-1 = n
	bool isFBT(TreeNode* root)
	{
        // 调用dp递归
        ReturnType ans = isFBTprocess(root);
        return ans.isf;
	}	
private:
	// 定制递归返回信息结构体
	struct ReturnType
	{
	    int deep; // 子树深度
	    int nodes; // 子树结点个数
	    bool isf; // 子树是否是满二叉树
	    ReturnType (int d, int n, bool is) // 构造函数
	    {
	        deep = d;
	        nodes = n;
	        isf = is;
	    }
	};
	// 声明递归函数
	ReturnType isFBTprocess(TreeNode* root)
	{
	    // 空树深度为0，结点数为0，是满二叉树
	    if (!root)
	    {
	        return ReturnType(0, 0, 1);
	    }
	    // 向左子树要信息
	    ReturnType leftdata = isFBTprocess(root->left);
	    ReturnType rightdata = isFBTprocess(root->right);
	    // 加工当前子树信息
	    int deep = 0, nodes = 0;
	    bool isf = true;
	    // 当前子树深度为最大子树深度+1
	    deep = leftdata.deep > rightdata.deep ? leftdata.deep+1 : rightdata.deep+1;
	    // 当前子树结点数等于左子树节点数加右子树节点数+1
	    nodes = leftdata.nodes + rightdata.nodes + 1;
	    // 如果左右子树任意一个不是满二叉树，则当前子树不是
	    if (!leftdata.isf || !rightdata.isf)
	    {
	        isf = false;
	    }
	    // 如果当前子树不满足满二叉树公式，则不是
	    if (pow(2, deep) != (nodes-1))
	    {
	        isf = false;
	    }
	    
	    return ReturnType(deep, nodes, isf);
	}
};
