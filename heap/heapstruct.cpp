/*
    堆结构
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class heap
{
public:
    vector<int> nums; // 存储数据
    int heapsize; // 堆的大小
    bool isgre; // 是否是大根堆
    bool (*cmp)(int, int); // 比较函数指针

    heap(bool isgre=true) // 给出大小顶堆，默认大顶堆
    {
        this->heapsize = 0; // 初始堆大小
        if (isgre) cmp = this->heapgreter;
        else cmp = this->heapless;
    }
public:
    // 堆中插入新元素，emplace
    void heapinsert(int data)
    {
        // 获取当前数组实际size
        int n = this->nums.size();
        // 插入元素在数组中的索引
        int index = heapsize;

        // 在heapsize位置添加新元素，同时heapsize++
        if (heapsize >= n)
        {
            nums.emplace_back(data);
            this->heapsize++;
        }
        else
        {
            this->nums[heapsize++] = data; // 加入新数据
        }
        
        // 新加入的元素向上调整,调整结构
        while ((*cmp)(this->nums[index], nums[(index-1)>>1])) // 但前索引位置元素大于或小于父节点值
        {
            // 交换当前结点与父节点的值
            myswap(this->nums, index, (index-1)>>1);
            index = (index-1)>>1;
        }
    }
    // 删除任意位置元素
    void heapify(int index)
    {
        // 将index位置元素调到堆尾
        myswap(this->nums, index, --heapsize);
        // index位置元素向下调整结构
        int left = (2*index) + 1; // 左孩子下标
        // 如果有左孩子
        while (left < heapsize)
        {
            // 找到左右孩子的最大值或最小值
            int largestindex = (left+1 < heapsize) && (*cmp)(nums[left+1], nums[left]) ? left+1 : left;
            // 判断index对应的元素与largestindex的关系
            largestindex = (*cmp)(nums[largestindex], nums[index]) ? largestindex : index;
            if (largestindex == index) // index的元素不是最大或最小
            {
                break;
            }
            // 交换元素
            myswap(this->nums, largestindex, index);
            index = largestindex;
            left = (2*index) + 1;
        }
    }
    // 获取堆顶元素,top()
    int gettop()
    {
        if (!this->heapsize) // 堆中没有元素
        {
            cout << "堆为空" << endl;
            return INT_MIN;
        }
        return this->nums[0];
    }
    // 判断堆是否为空,empty()
    bool isempty()
    {
        if (!this->heapsize) return true;
        else return false;
    }
    // 获取堆中元素个数
    int size()
    {
        return this->heapsize;
    }
private:
    // 交换数组中两个不同下标的元素
    void myswap(vector<int>& arr, int indexa, int indexb)
    {
        int temp = arr[indexa];
        arr[indexa] = arr[indexb];
        arr[indexb] = temp;
    }
    // 比较函数,大根堆
    static bool heapgreter(int a, int b)
    {
        return a > b;
    }
    // 比较函数，小根堆
    static bool heapless(int a, int b)
    {
        return a < b;
    }
};

int main()
{
    cout << "堆结构测试" << endl;

    vector<int> testarr{9,5,0,2,1,4,8,7,3,6};
    heap h; // 默认大根堆
    // 获取大小
    cout << h.size() << endl;
    // 是否为空
    cout << h.isempty() << endl;

    // 插入元素
    for (int i = 0; i < testarr.size(); ++i)
    {
        h.heapinsert(testarr[i]);
    }

    // 获取大小
    cout << h.size() << endl;
    // 是否为空
    cout << h.isempty() << endl;

    // 遍历,删除
    while (!h.isempty())
    {
        cout << h.gettop() << endl;
        h.heapify(0);
    }

    // for (int i = 0; i < testarr.size(); ++i)
    // {
    //     cout << testarr[i] << endl;
    // }

    return 0;
}
