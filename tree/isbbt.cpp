#include <iostream>
#include <cmath>

using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode (int val)
    {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class sloution
{
public:
    // 树型DP判断是否是平衡二叉树
    // 对于仁一颗子树，左右子树高度差不大于1即小于2
    bool isBBT (TreeNode* root)
    {
        ReturnInfo ans = isBBTDPprocess(root);
        return ans.isBB;
    }
private:
    // 定义树型DP递归返回信息
    struct ReturnInfo
    {
        bool isBB; // 子树是否是平衡二叉树
        int height; // 子树的高度
        ReturnInfo (bool is, int he) // 构造函数
        {
            this->isBB = is;
            this->height = he;
        }
    };
    // 树型DP递归函数
    ReturnInfo isBBTDPprocess(TreeNode* root)
    {
        // 终止条件，当节点为空时返回的信息
        if (!root)
        {
            return ReturnInfo(1, 0); // 空树被认为是平衡树，且高度为0
        }
        // 接受左子树信息
        ReturnInfo leftData = isBBTDPprocess(root->left);
        // 接受右子树信息
        ReturnInfo rightData = isBBTDPprocess(root->right);
        // 加工当前子树的返回信息
        bool isBB = true;
        int height = 0;
        // 当前子树高度为左右子树最高高度+1
        height = leftData.height > rightData.height ? leftData.height+1 : rightData.height+1;
        // 1.左右子树任一子树不是二叉平衡树
        // 2.左右子树高度差大于1
        if (!leftData.isBB || !rightData.isBB || (abs(leftData.height-rightData.height) > 1))
        {
            isBB = false;
        }
        
        // 返回当前子树信息
        return ReturnInfo(isBB, height);
    }
};
