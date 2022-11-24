#include <iostream>
#include <vector>
using namespace std;

/*
  时间复杂度O(n2),空间复杂度O(1),不稳定
  思想：双指针遍历数组，依次选择第i位到第n-1位的最小值或最大值放在第i位上
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
  
  void selectionsort(vector<int> nums)
  {
    int n = nums.size();
    // 特殊情况处理
    if (n < 2)
    {
      return;
    }
    
    for (int i = 0; i < n-1; ++i)
    {
      // 将第i位的元素设为初始最小值
      int minIndex = i;
      for (int j = i+1; j < n; ++j)
      {
        // 依次判断第i+1到第n-1的元素与最小下标元素的大小
        minIndex = nums[j] < nums[minIndex] ? j : minIndex;
      }
      // 比较完成，交换元素
      swap(nums[minIndex], nums[i]);
    }
  }
};
