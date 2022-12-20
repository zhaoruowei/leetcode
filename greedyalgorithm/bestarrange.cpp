/*
    会议室问题。
    给定一个时间段[start, end]。
    有n个会议，分别有各自的起始时间starti和结束时间endi
    问如何安排这些会议，使一天中举行的会议次数最多
    类似于CPU调度问题，采取结束时间最早的会议
*/

# include <iostream>
# include <vector>
# include <queue>

using namespace std;

class sloution
{
public:
    // starttime:一天的开始时间
    // endtime：一天的结束时间
    // programs：n*2的二维数组，保存一共n个会议需要安排，每个会议的开始时间n[i][0]和结束时间n[i][1]
    int bestarrange(int starttime, int endtime, vector<vector<int>> programs)
    {
        // 获取一共几个会议
        int n = programs.size();
        int ans = 0;
        if (n < 1) // 没有会议
        {
            return ans;
        }
        // 小顶堆
        priority_queue<vector<int>, vector<vector<int>>, cmp> heapprogram;
        // 遍历数组构建小顶堆
        for (int i = 0; i < n; ++i)
        {
            heapprogram.emplace(programs[i]);
        }

        int timepoint = starttime; // 当前时间点指针
        while (!heapprogram.empty())
        {
            // 弹出结束时间最早的会议
            vector<int> program = heapprogram.top();
            heapprogram.pop();
            // 判断当前时间点，是否早于会议的开始时间
            if (timepoint <= program[0])
            {
                // 时间点移动到结束时间
                timepoint = program[1];
                // 判断是否超时
                if (timepoint > endtime)
                {
                    break;
                }
                ans++;
            }
        }
        return ans;
    }
private:
    // 小顶堆比较函数
    struct cmp
    {
        bool operator()(vector<int> a, vector<int> b)
        {
            // 按结束时间比较
            return a[1] > b[1];
        }
    };
};

int main()
{
    cout << "贪心算法-会议室安排问题" << endl;

    int start = 6;
    int end = 18;
    vector<vector<int>> programs{{4,6}, {5,7}, {6,10}, {6,8}, {9,11}, {10,18}, {11,12}, {11,20}, {12,17}, {12, 15}, {12,14}, {15,18}, {18,20}};
    sloution s;
    cout << "最多安排" << s.bestarrange(start, end, programs) << endl;
    return 0;
}
