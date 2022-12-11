#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class sortalgorithm
{
public:
    void radixsort(vector<int>& nums)
    {
        int n = nums.size();
        if (n < 2)
        {
            return;
        }
        // 求数组中最大位数
        int digital = maxbits(nums);
        // 0-n-1范围上有序
        process(nums, 0, n-1, digital);
    }
private:
    // 获取数组中最大元素的位数
    int maxbits(vector<int> nums)
    {
        // 找到数组最大值
        int maxnum = INT_MIN;
        for (int i = 0; i < nums.size(); ++i)
        {
            maxnum = maxnum > nums[i] ? maxnum : nums[i];
        }
        // 求最大元素的位数
        int ans = 0;
        while (maxnum)
        {
            maxnum /= 10;
            ans++;
        }
        
        return ans;
    }
    // 获取整数的d位上的元素
    int getdigital(int val, int d)
    {
        int res = -1;
        while (d--)
        {
            res = val % 10;
            val /= 10;
        }
        return res;
    }
    void process(vector<int>& nums, int L, int R, int digital)
    {
        // 桶的数量，从0-9
        int radix = 10;
        // 辅助空间，存储进出桶的元素
        vector<int> bucket(R-L+1);
        // 从数字的1位到digital位进行进出桶排序
        for (int d = 1; d <= digital; ++d)
        {
            // 词频统计数组，记录每个数字位置的元素有几个
            vector<int> count(radix);
            // 统计每个元素d上的数字
            for (int i = L; i <= R; ++i)
            {
                int temp = getdigital(nums[i], d);
                count[temp]++;
            }
            // 将count数组变为累加和数组,表示小于等于i的数字共有几个
            for (int i = 1; i < radix; ++i)
            {
                count[i] += count[i-1];
            }
            // 数字出桶，从R到L
            for (int i = R; i >= L; --i)
            {
                int temp = getdigital(nums[i], d);
                bucket[--count[temp]] = nums[i];
            }
            // 将辅助桶中的元素输出到原数组，进行下一位数字的进出桶
            for (int i = 0; i < bucket.size(); ++i)
            {
                nums[i+L] = bucket[i];
            }
        }
    }
};
