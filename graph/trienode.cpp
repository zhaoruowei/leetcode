/*
    前缀树结构，用于字符串的子串统计等
    节点上没有值，通向下一个节点的路径上保存字符
    每个节点按字符个数有一个int型数组，数组上某一位下标的元素为0表示，该节点没有到该字符的路径
    比如，26个小写字母组成的前缀树，每个节点有26个大小的数组，数组[0]表示字符a，如果arr[0] 为1表示有通向a的路径，即a在两个节点的路径上
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class TrieNode
{
public:
    int pass; // 经过该字符的次数
    int end; // 以该字符结尾的次数
    // 数组下标对应26个字符，存储的结点表示存在这个字符
    vector<TrieNode*> path; // 保存通向对应字符的路径，如果字符种类较多可以用hashmap存储，以减少空间
    TrieNode()
    {
        this->pass = 0;
        this->end = 0;
        this->path = vector<TrieNode*> (26);
    }
// 前缀树相关操作及算法    
public:
    // 前缀树中插入字符串word
    void insertString(string word, TrieNode* root)
    {
        // 字符串长度
        int length = word.length();
        // 如果长度为0，返回
        if (!length || !root)
        {
            return;
        }
        // 每次建立一个结点就增加pass值
        root->pass++;
        // 临时指针指向root
        TrieNode* curnode = root;
        // 遍历字符串
        for (int i = 0; i < length; ++i)
        {
            // 求出当前字符在数组中的索引
            int index = word[i] - 'a'; // a的索引为0
            // 检查当前字符，是否在该结点下有路
            if (curnode->path[index] == nullptr) // 当前结点没有通向下一字符的路
            {
                // 新建一条通向当前遍历到字符的路
                curnode->path[index] = new TrieNode;
            }
            // 当前结点指针指向字符索引的node
            curnode = curnode->path[index];
            curnode->pass++;
        }
        // 遍历完所有字符，curnode指针指向通向最后一个字符的结点
        curnode->end++;
    }
    // 查找某一单词word一共加入过几次
    int searchString(string word, TrieNode* root)
    {
        int length = word.length();
        if (!length || !root) // 空字符串 空前缀树
        {
            return 0;
        }
        // 遍历字符串
        for (int i = 0; i < length; ++i)
        {
            // 取得字符在数组中的索引
            int index = word[i] - 'a';
            // 判断前缀树当前结点有没有经过a的路
            if (!root->path[index]) // 没有,表示没有当前字符
            {
                return 0;
            }
            else // 有路径
            {
                root = root->path[index];
            }
        }
        // 遍历结束，root停留在最后一个字符的结点上
        return root->end;
    }
    // 删除前缀树中加入过的字符
    void deleteString(string word, TrieNode* root)
    {
        int length = word.length();
        if (!length || !root || !searchString(word, root)) // 空字符串，空前缀树, 没有出现过
        {
            return;
        }

        unordered_set<TrieNode*> zeronode; // 存储需要析构的结点
        // 遍历字符串
        TrieNode* curnode = root;
        // 第一个结点的pass--
        curnode->pass--;
        
        for (int i = 0; i < length; ++i)
        {
            int index = word[i] - 'a';
            // 先保存下一节点的指针
            TrieNode* nextnode = curnode->path[index];
            // 如果当前结点的pass已经为0
            if (curnode->pass == 0)
            {
                // 当前结点加入析构set
                zeronode.emplace(curnode);
                curnode->path[index] = nullptr;
            }
            // 当前结点下移
            curnode = nextnode;
            curnode->pass--;
        }
        curnode->end--;
        if (!curnode->pass) zeronode.emplace(curnode);

        // 遍历set进行结点析构,root结点交给主函数析构
        for (auto node : zeronode)
        {
            if (node != nullptr && node != root) delete node;
            node = nullptr;
        }
    }
    // 检查一个前缀树中有几个以单词word为前缀
    int prefixNumber(string word, TrieNode* root)
    {
        if (!root) // 前缀树为空
        {
            return 0;
        }
        int length = word.length();
        // 遍历字符串
        for (int i = 0; i < length; ++i)
        {
            // 取得字符索引
            int index = word[i] - 'a';
            // 判断root中是否有当前字符
            if (!root->path[index]) // 为空没有字符
            {
                return 0;
            }
            else // 有当前字符
            {
                root = root->path[index];
            }
        }
        return root->pass;
    }
};

int main()
{
    cout << "前缀树结构" << endl;
    TrieNode* trie = new TrieNode;
    cout << "trie初始地址" << trie << endl;
    cout << "初始字符个数：" << trie->path.capacity() << endl;
    int index = 't' - 'a';
    cout << "t的索引：" << index << endl;
    // 构造前的t结点指针
    cout << "构造前的t结点指针：" << trie->path[index] << endl;

    string word1 = "test";
    string word2 = "best";
    trie->insertString(word1, trie);
    // trie->insertString(word2, trie);
    // 构造后的t结点指针
    cout << "构造后的t结点指针：" << trie->path[index] << endl;

    // searchString
    cout << "是否插入" << word1 << ":" << trie->searchString(word1, trie) << endl;

    // 析构
    trie->deleteString(word1, trie);
    // 析构后的t结点指针
    cout << "析构后的t结点指针：" << trie->path[index] << endl;
    // trie->deleteString(word2, trie);
    cout << "析构后trie的地址：" << trie << endl;

    // 前缀树插入两字符
    trie->insertString(word1, trie);
    trie->insertString(word2, trie);

    // 有几个以word为前缀的字符串
    string preword = "";
    cout << "以"<< preword << "为前缀的字符有：" <<trie->prefixNumber(preword, trie) << endl;
    preword.append("be");
    cout << "以"<< preword << "为前缀的字符有：" <<trie->prefixNumber(preword, trie) << endl;
    preword.append("bestt");
    cout << "以"<< preword << "为前缀的字符有：" <<trie->prefixNumber(preword, trie) << endl;
    // 析构
    trie->deleteString(word1, trie);
    trie->deleteString(word2, trie);

    if (trie) delete trie;
    return 0;
}
