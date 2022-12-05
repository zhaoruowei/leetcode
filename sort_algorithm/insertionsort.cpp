#include <iostream>
#include <vector>

using namespace std;

/*
  最差时间复杂度O(n2),最优时间复杂度O(n),平均时间复杂度O(n2)
  空间复杂度O(1)
  具有稳定性
*/

class sortalgorithm
{
public:
  void insertionsort(vector<int> nums)
  {
    int n = nums.size();
    if (n < 2)
    {
      return;
    }
    
    // 0-0位置有序
    // 想让0-i有序
    for (int i = 1; i < n; ++i)
    {
      for (int j = i-1; j > 0 && nums[j] > nums[j+1]; --j)
      {
        swap(nums[j], nums[j+1]);
      }
    }
  
  }
private:
  void swap(int a, int b)
  {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
  }

};
