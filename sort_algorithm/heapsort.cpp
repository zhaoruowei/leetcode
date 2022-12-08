#include <iostream>
#include <vector>
using namespace std;

class sortalgorithm
{
public:
    // 堆排序（大根堆，小根堆结构）
    void heapsort(vector<int>& nums)
    {
        int n = nums.size();
        if (n < 2)
        {
            return;
        }
        // 将数组构建大根堆
        for (int i = 1; i < n; ++i)
        {
            heapinsert(nums, i);
        }
        int heapsize = n;

        // 将堆顶元素与堆尾元素调换，进行heapify
        while (heapsize > 1)
        {
            myswap(nums[0], nums[--heapsize]);
            heapify(nums, 0, heapsize);
        }
    }
private:
    // 堆结构插入元素，插入点向上比较，父节点下标i-1/2
    void heapinsert(vector<int>& nums, int index)
    {
        // 当前节点下标元素大于父节点位置元素
        while (nums[index] > nums[(index-1)/2])
        {
            // 交换当前结点与父节点元素
            myswap(nums[index], nums[(index-1)/2]);
            // 下标变换
            index = ((index-1)/2);
        }
    }
    // 堆结构删除元素，删除位置与堆结构最后一个位置元素交换，交换后位置向下比较
    void heapify(vector<int>& nums, int index, int heapsize)
    {
        // 左孩子下标
        int left = (2*index) + 1;
        // 是否有孩子存在
        while (left < heapsize)
        {
            // 确定左右孩子中值最大的孩子的结点下标
            int largest = (left+1) < heapsize && nums[left+1] > nums[left] ? left+1 : left;
            // 判断最大孩子与当前位置元素大小
            largest = nums[largest] > nums[index] ? largest : index;
            // 如果当前位置大于最大孩子
            if (largest == index)
            {
                break;
            }
            // 否则将当前位置元素与最大孩子交换
            myswap(nums[largest], nums[index]);
            index = largest;
            left = (2*index) - 1;
        }
    }
    
    void myswap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
};
