#include <iostream>
#include <stack>

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
	// 前序递归
	void preOrder(TreeNode* root)
	{
		if (!root)
		{
			return;
		}
		cout << root->val << endl;
		preOrder(root->left);
		preOrder(root->right);
	}
	// 前序迭代
	void preOrderIteration(TreeNode* root)
	{
		if (!root)
		{
			return;
		}
		stack<TreeNode*> list;
		list.emplace(root);
		while (!list.empty())
		{
		    TreeNode* cur = list.top();
		    list.pop();
		    cout << cur->val << endl;
		    if (cur->right) list.emplace(cur->right);
		    if (cur->left) list.emplace(cur->left);
		}
	}
	// 中序递归
	void inOrder(TreeNode* root)
	{
	    if (!root)
	    {
	        return;
	    }
	    inOrder(root->left);
	    cout << root->val << endl;
	    inOrder(root->right);
	}
	// 中序迭代
	void inOrderIteration(TreeNode* root)
	{
	    if (!root)
	    {
	        return;
	    }
	    stack<TreeNode*> list;
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
	            cout << root->val << endl;
	            root = root->right;
	        }
	    }
	}
	// 后序递归
	void postOrder(TreeNode* root)
	{
	    if (!root)
	    {
	        return;
	    }
	    postOrder(root->left);
	    postOrder(root->right);
	    cout << root->val << endl;
	}
	// 后序迭代
	void postOrderIteration(TreeNode* root)
	{
	    if (!root)
	    {
	        return;
	    }
	    stack<TreeNode*> list1;
	    stack<TreeNode*> list2;
	    list1.emplace(root);
	    while (!list1.empty())
	    {
	        TreeNode* cur = list1.top();
	        list1.pop();
	        list2.emplace(cur);
	        if (cur->left) list1.emplace(cur->left);
	        if (cur->right) list1.emplace(cur->right);
	    }
	    while (!list2.empty())
	    {
	        TreeNode* cur = list2.top();
	        list2.pop();
	        cout << cur->val << endl;
	    }
	}
	// 广度优先遍历（层序遍历）
	void bfs(TreeNode* root)
	{
	    if (!root)
	    {
	        return;
	    }
	    queue<TreeNode*> list;
	    list.emplace(root);
	    while (!list.empty())
	    {
	        TreeNode* cur = list.front();
	        list.pop();
	        cout << cur->val << endl;
	        if (cur->left) list.emplace(cur->left);
	        if (cur->right) list.emplace(cur->right);
	    }
	}
	// 层序遍历分层输出
	vector<vector<int>> bfsEachFloor(TreeNode* root)
	{
	    // 存储所有层的结果
	    vector<vector<int>> ans;
	    // 存储每一层的结果
	    vector<int> res;
	    if (!root)
	    {
	        return ans;
	    }
	    // 辅助队列，用于层序遍历
	    queue<TreeNode*> list;
	    list.emplace(root);
	    // 记录当前层最后一个结点和下一层最后一个结点
	    TreeNode* curend = root; // 初始为root
	    TreeNode* nextend = nullptr; // 初始为空
	    // 遍历二叉树
	    while (!list.empty())
	    {
	        TreeNode* cur = list.front();
	        list.pop();
	        // 左右孩子入队，并更新nextend值
	        if (cur->left)
	        {
	            list.emplace(cur->left);
	            nextend = cur->left;
	        }
	        if (cur->right)
	        {
	            list.emplace(cur->right);
	            nextend = cur->right;
	        }
	        // 处理当前结点的值，判断当前结点是否是当前层最后一个节点
	        if (cur != curend) // 不时，在当前层数组中记录当前节点值
	        {
	            res.emplace_back(cur->val);
	        }
	        else // 是当前层最后一个结点，进行结算
	        {
                curend = nextend; // 重置当前层最后一个结点为下一层最后一个结点
                nextend = nullptr; // 重置下一层最后一个节点
                res.emplace_back(cur->val); // 记录最后一个节点的值
                ans.emplace_back(res); // 存储当前层结果
                res.clear(); // 重置每层存储数组
	        }
	    }
	    return ans;
	}
};
