/*
最小花费，分割金条问题
分割一条金条，每次分割费用等于当前金条长度，需要将金条分割成若干份，每一份长度存储在数据中vector<int> length
问如何分割花费最小
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class sloution
{
public:
    int lessmoneysplitgold(vector<int> targetlength)
    {
        int n = targetlength.size();
        if (n < 2) return 0;
        if (n < 3) return targetlength[0] + targetlength[1];
        // 优先级队列，按需要长度排序，小顶堆，(系统默认大根堆)
        priority_queue<int, vector<int>, greater<int>> lengthheap;
        for (int i = 0; i < n; ++i)
        {
            lengthheap.emplace(targetlength[i]);
        }

        int cost = 0;
        while (lengthheap.size() != 1)
        {
            // 每次弹出最短的两个数字
            int short1 = lengthheap.top();
            lengthheap.pop();
            int short2 = lengthheap.top();
            lengthheap.pop();
            // 求最短的两个数的和
            cost += short1 + short2;
            // 和放入小根堆
            lengthheap.emplace(short1 + short2);
        }

        return cost;
    }
};

int main()
{
    cout << "贪心算法-金条分割问题" << endl;
    // vector<int> targetlength{10,10,20,25,25,60};
    vector<int> targetlength{10,20,30};
    sloution s;
    cout << s.lessmoneysplitgold(targetlength) << endl;
    return 0;
}
