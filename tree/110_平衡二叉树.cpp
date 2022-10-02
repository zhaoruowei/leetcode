class Solution {
public:
    struct ReturnType
    {
        int high;
        bool isBalance;
    };

public:
    bool isBalanced(TreeNode* root) {
        // 平衡二叉树满足任意子树的左右子树高度差不超过1
        // 判断条件：1.左子树为平衡二叉树，2.右子树为平衡二叉树，3.左右子树高度差小于2
        // 因此每次递归需要判断高度差和左右树是否都是平衡二叉树，所以每次递归有两个返回值
        // 自定义一个结构体用于返回结果
        // 调用递归函数
        ReturnType ans = process(root);
        return ans.isBalance;
    }
    // 递归函数
    ReturnType process(TreeNode *root)
    {
        // 递归出口
        if (root == nullptr)
        {
            ReturnType res;
            res.high = 0;
            res.isBalance = true;
            return res;
        }
        // 遍历左子树
        ReturnType leftres = process(root->left);
        // 遍历右子树
        ReturnType rightres = process(root->right);
        // 根据左右子树结果，处理当前结点
        ReturnType res;
        // 当前结点高度为左右子树最大高度+1
        res.high = leftres.high > rightres.high ? leftres.high+1 : rightres.high+1;
        // 判断当前结点子树是否平衡，满足条件1，2，3
        res.isBalance = leftres.isBalance && rightres.isBalance && (abs(leftres.high - rightres.high) < 2);
        // 返回当前结点结果
        return res;
    }
};
