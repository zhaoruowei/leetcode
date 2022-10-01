class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        // 迭代，双栈
        vector<int> ans;
        if (root != nullptr)
        {
            stack<TreeNode*> ts1;
            stack<TreeNode*> ts2;
            // 根结点入栈1
            ts1.push(root);
            while (!ts1.empty())
            {
                // 根结点出栈1，入栈2
                root = ts1.top();
                ts1.pop();
                ts2.push(root);
                // 如果有左孩子，左孩子入栈1
                if (root->left != nullptr)
                {
                    ts1.push(root->left);
                }
                // 如果有右孩子，右孩子入栈1
                if (root->right != nullptr)
                {
                    ts1.push(root->right);
                }
            }
            // 遍历栈2，打印
            while (!ts2.empty())
            {
                root = ts2.top();
                ts2.pop();
                ans.push_back(root->val);
            }
        }
        return ans;

        // // 递归
        // vector<int> ans;
        // postorder(root, ans);
        // return ans;
    }
    void postorder(TreeNode *node, vector<int> &ans)
    {
        if (!node)
        {
            return;
        }
        // 遍历左孩子
        postorder(node->left, ans);
        // 遍历右孩子
        postorder(node->right, ans);
        // 打印根结点
        ans.push_back(node->val);
    }
};
