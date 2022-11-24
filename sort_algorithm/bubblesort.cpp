#include <iostream>
#include <vector>
using namespace std;

/*
  时间复杂度O(n2),空间复杂度O(1),稳定
  思想：依次将第i位与第i+1位元素比较，较大或较小元素右移，每一轮完成后最后一个元素为排序完成的最大值或最小值
*/

class sortalgorithm
{
public:
  void swap(int a, int b)
  {
    int temp = a;
    a = b;
    b = temp;
  }
  
  void bubblesort(vector<int> nums)
  {
    int n = nums.size();
    // 特殊情况
    if (n < 2)
    {
      return;
    }
    // 确定一共排序几轮(n)
    for (int i = n-1; i > 0; --i)
    {
      // 每一轮对0到i位置上的元素逐一比较
      for (int j = 0; j < i; ++j)
      {
        // 较大的数右移
        if (nums[j] > nums[j+1])
        {
          swap(nums[j], nums[j+1]);
        }
      }
    }
  }

};
