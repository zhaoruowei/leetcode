/*
并查集结构
UnionFindeSet(T) ,将用户给的初始数据构造成加工的结点数据，看作每个元素属于自己的集合
isSameSet(T1, T2),用户给定两个参数，判断是否处于同一个集合
UnionSet(T1, T2),用户给的两个参数，如果不在一个集合就进行合并

逻辑结构是，将所有元素加工成一个结点。初始时每个结点属于自己的一个集合。每个结点有一个向上指的指针，集合最顶部的结点的指针指向自己。
初始每个元素都是自己集合中的最顶结点（称为代表节点）向上的指针指向自己。
判断两个元素是否在同一集合时，找到两个元素对应的两个结点，同时将两个结点的向上指针走到顶，找到所在集合的代表结点，如果两个代表结点相同，那么属于同一个集合，否则不是一个集合
合并时，将所在集合结点较少的顶部代表结点的向上指针，指向结点较多的集合的代表结点。
注意：如果向上指针的结点数过多，会导致在查找代表节点时的时间消耗过大。所以需要在向上找代表结点的过程中，扁平化所有底部结点，直接指向代表节点。
这样，只要操作集合时findhead操作足够多，就能实现近似于O(1)的复杂度。
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

// 并查集结构
template <typename T>
class UnionFindeSet
{
private:
    // 自定义结构体，类似于点
    struct Element
    {
        T val;
        Element(T val): val(val) {};
    };
public:
    unordered_map<T, Element*> elementmap; // 将用户输入的T类型数据，转换为Element*类型，并形成对照表
    unordered_map<Element*, Element*> fathermap; // 一个element集合的父集合对照表
    unordered_map<Element*, int> sizemap; // 一个父集合的代表结点中下属的结点一共有多少个

    UnionFindeSet(vector<T>& list)
    {
        // 构造函数，用户输入一个T类型的数组，包括所有操作的元素
        int n = list.size();
        // 遍历数组中的所有元素，构造每个元素的初始结点进行初始化
        for (int i = 0; i < n; ++i)
        {
            // 判断是否是重复元素
            if (elementmap.find(list[i]) == elementmap.end()) // 新元素
            {
                // 构造新结点
                Element* element = new Element(list[i]);
                // 结点map中添加记录
                this->elementmap.emplace(list[i], element);
                // 当前结点的父节点指向自己
                this->fathermap.emplace(element, element);
                // 当前结点所在集合的代表节点所在集合的值置为1
                this->sizemap.emplace(element, 1);
            }
        }
    }
    // 析构函数，创建的每一个element都要进行析构
    ~UnionFindeSet()
    {
        for (auto& kvnode : this->elementmap)
        {
            if (kvnode.second != nullptr) delete kvnode.second;
            kvnode.second = nullptr;
        }
    }
public:
    // 判断两个元素是否属于一个集合
    bool isSameSet(T a, T b)
    {
        // 判断两个元素是否已经初始化
        if (this->elementmap.find(a) != this->elementmap.end() && this->elementmap.find(b) != this->elementmap.end())
        {
            // 两个元素所在集合的代表结点是否是同一个结点
            if (findHead(this->elementmap[a]) == findHead(this->elementmap[b])) return true;
        }
        return false; // 至少有一个元素不在初始化的并查集中
    }
    // 合并两个不在一个集合中的结点
    void UnionSet(T a, T b)
    {
        // 判断两个元素是否都在初始化结构中
        if (this->elementmap.find(a) != this->elementmap.end() && this->elementmap.find(b) != this->elementmap.end())
        {
            // 判断两个元素是否属于一个集合
            if (!isSameSet(a, b)) // 不属于一个集合进行合并
            {
                // 找到两个结点所在集合的代表节点
                Element* headA = findHead(this->elementmap[a]);
                Element* headB = findHead(this->elementmap[b]);
                // 判断两个代表结点所在的集合哪个结点数更多
                Element* big = this->sizemap[headA] > this->sizemap[headB] ? headA : headB; // big指向结点更多的集合
                Element* small = big == headA ? headB : headA; // samll指向结点更少的集合
                // 将结点少的代表结点指向结点多的代表结点
                this->fathermap[small] = big;
                // 更新合并后集合的节点数
                this->sizemap[big] += this->sizemap[small];
                // 清空samll作为代表节点的集合数据
                this->sizemap.erase(this->sizemap.find(small));
            }
        }
    }
private:
    // 给定一个结点，找到该节点所在集合的代表结点
    Element* findHead(Element* element)
    {
        // stack，优化代表结点下属结点过长导致的合并，检查操作的时间消耗
        stack<Element*> list;
        // 不断在fathermap中遍历element结点，直到element的fathermap指向自己，表示找到了代表结点
        while (this->fathermap[element] != element)
        {
            // 将遍历的所有结点压入辅助栈中
            list.emplace(element);
            element = this->fathermap[element];
        }
        // 结束遍历时，element指向所在集合的代表结点
        // 逐个弹出栈中元素，将所有元素的father直接指向所在集合的代表节点，进行扁平化处理
        while (!list.empty())
        {
            Element* curelement = list.top(); list.pop();
            this->fathermap[curelement] = element;
        }

        return element;
    }
};

int main()
{
    cout << "并查集结构测试" << endl;

    vector<int> test{1,2,3,4,5,6,7,8};
    // 初始化
    UnionFindeSet<int> uset(test);
    cout << "1和2是一个集合吗？" << uset.isSameSet(1,2) << endl;
    cout << "1和9是一个集合吗？" << uset.isSameSet(1,9) << endl;
    cout << "5和8是一个集合吗？" << uset.isSameSet(5,8) << endl;
    cout << "合并所有奇数" << endl;
    uset.UnionSet(1,3);
    uset.UnionSet(1,5);
    uset.UnionSet(1,7);
    cout << "1和7是一个集合吗？" << uset.isSameSet(1,7) << endl;
    cout << "1和4是一个集合吗？" << uset.isSameSet(1,4) << endl;
    return 0;
}
