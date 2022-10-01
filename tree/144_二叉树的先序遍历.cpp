class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        // 迭代，栈
        vector<int> ans;
        if (root != nullptr)
        {
            stack<TreeNode*> ts;
            // 根节点入栈
            ts.push(root);
            while (!ts.empty())
            {
                // 根结点出栈
                root = ts.top();
                ts.pop();
                // 打印
                ans.push_back(root->val);
                // 右孩子不为空，入栈
                if (root->right != nullptr)
                {
                    ts.push(root->right);
                }
                // 左孩子不为空，入栈
                if (root->left != nullptr)
                {
                    ts.push(root->left);
                }
            }
        }
        return ans;
        
        // // 递归
        // vector<int> ans;
        // preorder(root, ans);
        // return ans;
    }
    void preorder(TreeNode* node, vector<int> &ans)
    {
        if (!node)
        {
            return;
        }
        // 打印头结点
        ans.push_back(node->val);
        // 遍历左结点
        preorder(node->left, ans);
        // 遍历右结点
        preorder(node->right, ans);
    }
};
