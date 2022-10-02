class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // // 递归
        // // 返回信息为结点
        // // 加工信息，1.如果子树有p，没有q返回p
        // // 2.如果子树有q，没有p返回q
        // // 3.如果子树有q，有p返回当前结点
        // // 4.如果子树没有p没有q返回空
        // // 递归出口,情况1，2，4
        // if (root == nullptr || root == p || root == q)
        // {
        //     return root;
        // }
        // // 接收左子树信息
        // TreeNode *leftres = lowestCommonAncestor(root->left, p, q);
        // // 接收右子树信息
        // TreeNode *rightres = lowestCommonAncestor(root->right, p, q);

        // // 加工信息
        // if (leftres != nullptr && rightres != nullptr)
        // {
        //     return root;
        // }

        // // 返回信息
        // return leftres != nullptr ? leftres : rightres;

        // 迭代，借助辅助哈希表和哈希集合
        // 辅助哈希表，记录每个结点的父节点
        unordered_map<TreeNode*, TreeNode*> fathermap;
        // 把根结点加入hashmap
        fathermap[root] = root;
        preorder(root, fathermap);

        // 辅助哈希set，根据父节点哈希表回溯p结点到根结点的路径
        unordered_set<TreeNode*> routeset;
        TreeNode *cur = p;
        while (cur != fathermap[cur])
        {
            routeset.insert(cur);
            cur = fathermap[cur];
        }
        routeset.insert(root);
        
        cur = q;
        // 回溯结点q，比对路径set，如果回溯到的结点在set中就返回
        while (cur != fathermap[cur])
        {
            if (routeset.find(cur) != routeset.end())
            {
                break;
            }
            cur = fathermap[cur];
        }

        return cur;
    }
    // 递归先序遍历树
    void preorder(TreeNode *root, unordered_map<TreeNode*, TreeNode*> &fathermap)
    {
        if (root == nullptr)
        {
            return;
        }
        // 加入哈希表
        fathermap[root->left] = root;
        fathermap[root->right] = root;

        // 遍历左子树
        preorder(root->left, fathermap);
        // 遍历右子树
        preorder(root->right, fathermap);
    }
};
