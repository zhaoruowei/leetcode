#include <iostream>
#include <stack>
#include <climits>
#include <queue>
#include <cmath>

using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
public:
    TreeNode()
    {}
    TreeNode(int val)
    {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
// ========================================================================================    
    // 判断一颗二叉树是否是二叉搜索树（左子树小于根结点小于右子树）
    // 中序遍历二叉树，如果遍历结果为严格递增序列，则为二叉搜索树
    // 否则不是二叉搜索树
    // 递归,设置一个全局变量，记录上一个遍历的结点值
    int prenodeval = INT_MIN;
    bool isBST1(TreeNode *root)
    {
        if (root == nullptr)
        {
            return true;
        }
        // 遍历左子树
        bool isLeftBst = isBST1(root->left);
        // 如果左子树不满足，直接返回false
        if (!isLeftBst)
        {
            return false;
        }
        // 判断根结点值是否大于左结点
        if (root->val <= prenodeval)
        {
            return false;
        }
        prenodeval = root->val;
        // 遍历右子树
        return isBST1(root->right);
    }
    // 迭代
    bool isBST2(TreeNode *root)
    {
        if (root != nullptr)
        {
            // 辅助栈
            stack<TreeNode*> ts;
            // 根结点入栈
            // 如国当前结点有左孩子就进栈，否则出栈
            // 出栈时，有右孩子就近栈
            while (!ts.empty() || root != nullptr)
            {
                if (root != nullptr)
                {
                    ts.push(root);
                    root = root->left;
                }
                else
                {
                    // 出栈
                    root = ts.top();
                    ts.pop();
                    // 将中序遍历的打印行为，改为比较结点行为
                    if (root->val <= prenodeval)
                    {
                        return false;
                    }
                    prenodeval = root->val;
                    // 右孩子进栈
                    root = root->right;
                }
            }
        }
        return true;
    }
// =================================================================================================================
    // 判断是否是完全二叉树
    // 条件1，任意一结点不存在有右无左的情况
    // 条件2，在满足条件1的前提下，第一个遇到没有左右孩子的结点后的所有结点都是叶子结点
    bool isCBT(TreeNode *root)
    {
        // 广度优先遍历，判断是否满足条件1，2
        if (root == nullptr)
        {
            return true;
        }
        // 辅助队列
        queue<TreeNode*> que;
        // 根结点入队
        que.push(root);
        // 判断是否是叶子结点
        bool leaf = false;
        // 左孩子
        TreeNode *l = nullptr;
        // 右孩子
        TreeNode *r = nullptr;
        while (!que.empty())
        {
            // 队头结点出队
            root = que.front();
            que.pop();
            // 打印改为判断两个条件
            l = root->left;
            r = root->right;
            // 条件1 || 条件2
            if ((l == nullptr && r != nullptr) || (leaf && !(l == nullptr && r == nullptr)))
            {
                return false;
            }
            
            // 左孩子入队
            if (l != nullptr)
            {
                que.push(l);
            }
            // 右孩子入队
            if (r != nullptr)
            {
                que.push(r);
            }
            // 判断是否是第一个左右孩子不全的点
            if (l == nullptr || r == nullptr)
            {
                leaf = true;
            }
        }
        return true;
    }
// ============================================================================================    
    // 判断是否是满二叉树
    // 条件，一颗二叉树的深度为d，结点个数为n，满足2^d = n - 1
    // 1.确定返回信息的结构体
    struct FBTInfo
    {
        int d; // 深度
        int n; // 结点个数
        bool isFbt; // 是否是满二叉树
    };
    // 2.主函数
    bool isFBT(TreeNode *root)
    {
        FBTInfo ans;
        // 调用递归函数
        ans = processFBT(root);
        return ans.isFbt;
    }
    // 3.递归函数
    FBTInfo processFBT(TreeNode* root)
    {
        // 递归出口
        if (root == nullptr)
        {
            FBTInfo res;
            res.d = 0;
            res.n = 0;
            res.isFbt = true;
            return res;
        }
        // 接收左子树信息
        FBTInfo leftres = processFBT(root->left);
        // 接收右子树信息
        FBTInfo rightres = processFBT(root->right);
        
        // 加工当前结点信息
        FBTInfo res;
        // 当前结点深度
        res.d = leftres.d > rightres.d ? leftres.d + 1 : rightres.d + 1;
        // 当前结点子树的所有结点个数
        res.n = leftres.n + rightres.n + 1;
        // 当前结点是否是满二叉树
        res.isFbt = (leftres.isFbt && rightres.isFbt && (pow(2, res.d) == res.n - 1));
        
        // 返回当前结点信息
        return res;
    }
};

int main()
{
    // 右移运算符相当于log2(n)
    cout << log2(4) << endl;
    cout << (4 >> 1) << endl;
    // 左移运算符相当于2^n
    cout << pow(2, 3) << endl;
    cout << (1 << 3) << endl;

    return 0;
}
