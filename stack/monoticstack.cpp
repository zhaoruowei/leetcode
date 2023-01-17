/*
 单调栈结构，求数组中每个元素左右侧第一个大于或小于该元素的下标	
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class MonoticStack
{
public:
	// 获取左右两侧第一个大于该位置元素的下标，没有用-1表示，返回一个长度为n的数组，数组中first表示左侧元素下标，second表示右侧元素下标
	vector<pair<int, int>> getFirstBig(vector<int> &arr)
	{
		int n = arr.size();
		if (n < 1)
			return {};
		// 准备一个单调栈结构，因为数组中存在重复元素所以栈中存放vector数组，数组中存放的是下标
		stack<vector<int>> asc; // 栈中下标对应的元素值，单调递减
		// 记录结果
		vector<pair<int, int>> ans(n);
		// 遍历数组，将元素进栈
		for (int i = 0; i < n; ++i)
		{
			// 数据进栈，先判断是否大于栈顶元素，如果是就先弹栈，并结算弹出的下标
			while (!asc.empty() && arr[i] > arr[asc.top()[0]])
			{
				// 接收弹出的数组
				vector<int> curvector = asc.top();
				asc.pop();
				// 结算弹出的数组中的下标，右侧第一个大于元素下标为当前下标，左侧第一个下标为栈中的下一层数组的末尾元素
				// 遍历当前层弹出的数组，进行结算
				for (int j = 0; j < curvector.size(); ++j)
				{
					int left = asc.empty() ? -1 : asc.top()[asc.top().size()-1];
					ans[curvector[j]] = make_pair(left, i);
				}
			}
			// 直到单调栈为空，或者，不大于栈顶元素时
			if (asc.empty() || arr[i] < arr[asc.top()[0]]) // 栈为空或者当前元素小于栈顶元素，新建vector
			{
				vector<int> res{i};
				asc.emplace(res);
			}
			else // 栈不为空,且于栈顶元素相等， 加入栈顶数组的尾部
			{
				asc.top().emplace_back(i);
			}
		}
		// 遍历完数组，栈中还剩下的元素进行结算,右侧为-1，左侧为栈中的下一层数组的末尾
		while (!asc.empty())
		{
			vector<int> curvector = asc.top();
			asc.pop();
			for (int j = 0; j < curvector.size(); ++j)
			{
				int left = asc.empty() ? -1 : asc.top()[asc.top().size()-1];
				ans[curvector[j]] = make_pair(left, -1);
			}
		}
		return ans;
	}
};
