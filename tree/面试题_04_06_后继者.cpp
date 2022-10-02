class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        // 没有父指针，中序遍历，得到一个vector，找到p在vector中的下一个结点
        // 辅助vector,维护p和p的后继
        vector<TreeNode*> nodelist;
        inorder(root, nodelist, p);
        return  nodelist.size() == 2 ? nodelist[1] : nullptr;
    }
    void inorder(TreeNode* root, vector<TreeNode*> &nodelist, TreeNode *p)
    {
        if (root == nullptr)
        {
            return;
        }
        inorder(root->left, nodelist, p);
        if (root == p || nodelist.size() == 1)
        {
            nodelist.push_back(root);
        }
        inorder(root->right, nodelist, p);
    }
  
public:
  TreeNode *parent; // 父指针，指向当前结点的父节点

public:
  TreeNode* inorderSuccessorParent(TreeNode *root, TreeNode *p)
  {
    // 有父指针存在，结点p的后继有三种情况
    // 1.p有右子树，则p的后继为右子树的最左结点
    // 2.p无右子树，向上找p的父节点，一只找到父节点是父节点的父节点的左孩子的结点，即为p的后继
    // 3.不满足1，2，即p是右子树的最右结点，则p没有后继结点
    if (p == nullptr)
    {
      return nullptr;
    }
    // 有右子树
    if (p->right != nullptr)
    {
      // 一直遍历右子树的左节点
      p = p->right;
      while (p->left != nullptr)
      {
        p = p->left;
      }
    }
    else // 无右子树，向上遍历
    {
      TreeNode *parent = p->parent;
      while (parent != nullptr && p != parent->left)
      {
        p = parent;
        parent = p->parent;
      }
    }
    return p;
  }
  
};

