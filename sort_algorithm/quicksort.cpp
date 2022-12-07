#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

/*

*/

class sortalgorithm
{
public:
	void quicksort(vector<int>& nums)
	{
		int n = nums.size();
		if (n < 2)
		{
			return;
		}
		// 生成随机数种子
		srand((unsigned int)time(0));
		
		int L = 0, R = n-1;
		process(nums, L, R);
	}
private:
	void process(vector<int>& nums, int L, int R)
	{
		// 左边界小于右边界时
		if (L < R)
		{
			// L到R区间内随机选择一个数
			int index = rand() % ((R-L)+1) + L;
			// 随机位置数与右边界数交换，做为比较索引
			myswap(nums[index], nums[R]);
			// 区间内进行partition
			vector<int> res = partition(nums, L, R);
			// 等于区左侧进行process
			process(nums, L, res[0]-1);
			// 等于区右侧进行process
			process(nums, res[1]+1, R);
		}		
	}
	vector<int> partition(vector<int>& nums, int L, int R)
	{
		// 确定小于区域右边界
		int less = L - 1;
		// 确定大于区域左边界
		int more = R;
		while (L < more)
		{
			if (nums[L] < nums[R])
			{
                myswap(nums[++less], nums[L++]);
			}
			else if (nums[L] == nums[R])
			{
				L++;
			}
			else
			{
                myswap(nums[--more], nums[L]);
			}
		}
        myswap(nums[more], nums[R]);

		return {less+1, more};
	}
	void myswap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
};
