class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        // 迭代，栈
        vector<int> ans;
        if (root != nullptr)
        {
            stack<TreeNode*> ts;
            while (!ts.empty() || root != nullptr)
            {
                // 有左孩子就入栈
                if (root != nullptr)
                {
                    ts.push(root);
                    root = root->left;
                }
                else
                {
                    // 没有左孩子，弹栈
                    root = ts.top();
                    ts.pop();
                    // 打印
                    ans.push_back(root->val);
                    // 如果有右孩子，入栈
                    root = root->right;
                }
            }
        }
        return ans;

        // // 递归
        // vector<int> ans;
        // inorder(root, ans);
        // return ans;
    }
    void inorder(TreeNode *node, vector<int> &ans)
    {
        if (node == nullptr)
        {
            return;
        }
        // 遍历左子树
        inorder(node->left, ans);
        // 打印
        ans.push_back(node->val);
        // 遍历右子树
        inorder(node->right, ans);
    }
};
