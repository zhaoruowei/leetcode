/*
最大收益问题
vector<int> costs;  vector<int> profits;两个数组分别对应每个项目的花费与收益。
int k 表示最多串行的做几个项目，int m 表示你的初始资金
问按什么顺序做任务使利润最大
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class sloution
{
public:
    vector<int> mostprofit(vector<int> costs, vector<int> profits, int k, int m)
    {
        vector<int> ans;
        int cn = costs.size();
        int pn = profits.size();
        if (!cn || !pn || cn != pn || !k)
        {
            return ans;
        }
        // 按收益排序的大顶堆,pair.first是项目编号，pair.second是项目收益
        priority_queue<pair<int, int>, vector<pair<int, int>>, lesscmp> profitheap;
        // 存储已经做过的项目
        unordered_set<int> done;
        // 但钱手上可用资金
        int cur = m;
        for (int i = 0; i < k; ++i)
        {
            // 根据当前可用资金cur挑选costs中可实施的项目
            for (int j = 0; j < cn; ++j)
            {
                // 当前金额可以做该项目，且该项目没有解锁
                if (cur >= costs[j] && done.find(j) == done.end())
                {
                    // 将项目编号加入已解锁set
                    done.emplace(j);
                    // 将项目加入按收益排序的大根堆
                    profitheap.emplace(make_pair(j, profits[j]));
                }
            }
            // 如果没有可以做的项目，返回
            if (profitheap.empty())
            {
                break;
            }
            // 弹出已解锁的最大收益项目
            pair<int, int> program = profitheap.top();
            profitheap.pop();
            // 更新金额
            cur += profits[program.first];
            // 记录项目号
            ans.emplace_back(program.first+1);
        }
        return ans;
    }
    // 优化，使用小根堆结构，维护最小花费搜索
    vector<int> mostprofitup(vector<int> costs, vector<int> profits, int k, int m)
    {
        vector<int> ans;
        int cn = costs.size();
        int pn = profits.size();
        if (!cn || !pn || cn != pn || !k)
        {
            return ans;
        }
        // 按收益排序的大顶堆,pair.first是项目编号，pair.second是项目收益
        priority_queue<pair<int, int>, vector<pair<int, int>>, lesscmp> profitheap;
        // 按花费排序的小根堆，pair.first是项目编号，pair.second是项目花费
        priority_queue<pair<int, int>, vector<pair<int, int>>, grecmp> costheap;
        // 将所有项目按花费大小入小顶堆
        for (int i = 0; i < cn; ++i)
        {
            costheap.emplace(make_pair(i, costs[i]));
        }
        // 当前金额
        int cur = m;
        // 按项目执行次数循环
        for (int i = 0; i < k; ++i)
        {
            // 解锁当前金额可以做的项目
            while (!costheap.empty() && cur >= costheap.top().second) // heap中还有没解锁的项目，当前资金可以解锁
            {
                // 弹出解锁的项目进入按收益排序的大根堆
                profitheap.emplace(make_pair(costheap.top().first, profits[costheap.top().first]));
                costheap.pop();
            }
            // 选择收益最大的项目开始做
            if (!profitheap.empty())
            {
                pair<int, int> program = profitheap.top();
                profitheap.pop();
                cur += program.second;
                ans.emplace_back(program.first+1);
            }
        }

        return ans;
    }
private:
    struct lesscmp
    {
        bool operator()(pair<int, int> a, pair<int, int> b)
        {
            return a.second < b.second;
        }
    };
    struct grecmp
    {
        bool operator()(pair<int, int> a, pair<int, int> b)
        {
            return a.second > b.second;
        }
    };
};

int main()
{
    cout << "最大收益问题" << endl;
    vector<int> costs{3,1,4,9,9};
    vector<int> profits{1,2,3,7,4};
    int k = 4;
    int m = 1;
    vector<int> ans;
    sloution s;
    // ans = s.mostprofit(costs, profits, k, m);
    ans = s.mostprofitup(costs, profits, k, m);
    for (int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << endl;
    }
    return 0;
}
