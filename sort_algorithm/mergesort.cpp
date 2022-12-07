#include <iostream>
#include <vector>

using namespace std;

/*
  L-R的数组想有序，先让L到m上有序，再让m+1到R上有序，再合并两个有序数组即可
  时间复杂度符合master公式，T(N) = 2 * (N/2) + O(N), log2(2) == N^1, O(nlogn)
  空间复杂度O(n)
  具备稳定性
*/


class sortalgorithm
{
public:
  void mergesort(vector<int> nums)
  {
    int n = nums.size();
    if (n < 2)
    {
      return;
    }
    int L = 0, R = n-1, mid = L + ((R-L) >> 1);
    // 调用递归,使L到R区间有序
    process(nums, L, R);
  }
private:
  // 递归过程
  void process(vector<int>& nums, int L, int R)
  {
    // 当左边界等于右边界，表示只有一个数，有序，退出
    if (L == R)
    {
      return;
    }
    // 求出中值
    int mid = L + ((R-L) >> 1);
    // 左侧调用递归,使L到mid有序
    process(nums, L, mid);
    // 右侧调用递归，使mid+1到R有序
    process(nums, mid+1, R);
    // 合并两个区间
    merge(nums, L, mid, R);
  }
  // 合并过程
  void merge(vector<int>& nums, int L, int mid, int R)
  {
    // 辅助数组，用于保存左右区间合并的结果
    vector<int> help(R-L+1);
    // 辅助数组指针，指向辅助数组起始位置
    int i = 0;
    // 合并左右两区间,双指针指向两个区间的起始位置
    int p1 = L, p2 = mid + 1;
    while (p1 <= mid && p2 <= R)
    {
      // 将p1，p2位置较小的元素填入help数组
      help[i++] = nums[p1] < nums[p2] ? nums[p1++] : nums[p2++];
    }
    // 判断p1和p2是否还有剩余的元素
    while (p1 <= mid)
    {
      help[i++] = nums[p1++];
    }
    while (p2 <= R)
    {
      help[i++] = nums[p2++];
    }
    // 将help赋值给nums
    for (i = 0; i < help.size(); ++i)
    {
      nums[L+i] = help[i];
    }
  }
};
