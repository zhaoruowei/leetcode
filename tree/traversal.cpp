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
	// 后续递归
	void postOrder(TreeNode* root)
	{
	    if (!root)
	    {
	        return;
	    }
	    postOrder(root->left);
	    postOrder(root->right);
	    cout << root->val << end;
	}
	// 后续迭代
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
};
