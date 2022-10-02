// 接收信息是左右孩子的指针
// 加工信息是调换左右孩子
// 每次返回的信息是当前结点的指针

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr)
        {
            return nullptr;
        }
        
        TreeNode *l = invertTree(root->left);
        TreeNode *r = invertTree(root->right);

        TreeNode *temp = l;
        l = r;
        r = temp;
        root->left = l;
        root->right = r;
        return root;
    }
};
