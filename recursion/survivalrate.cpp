/*
    计算存活率，给定一个m*n的矩阵，Bob初始位于x，y位置，每次移动Bob都等概率的向上下左右四个方向任一方向移动
    问移动k次后，Bob还在矩阵内的概率是多少？
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

class Bob
{
public:
    static int rate_1(int m, int n, int x, int y, int k)
    {
        if (m < 1 || n < 1)
            return 0;
        // 计算Bob，移动k次，一共的方法
        int count = pow(4, k); // 每次移动有4种可能，移动k次，总的可能有4^k次
        // 计算存活的移动次数
        int res = process_1(x, y, k, m, n);
        return res / count;
    }
    static int rate_2(int m, int n, int x, int y, int k)
    {
        if (m < 1 || n < 1)
            return 0;
        // 准备三维数组作为缓存
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        // 计算Bob，移动k次，一共的方法
        int count = pow(4, k); // 每次移动有4种可能，移动k次，总的可能有4^k次
        // 计算存活的移动次数
        int res = process_2(x, y, k, m, n, dp);
        return res / count;
    }
    // 严格表结构
    static int rate_3(int m, int n, int x, int y, int k)
    {
        if (m < 1 || n < 1)
            return 0;
        int count = pow(4, k);
        // 移动方向的数组
        vector<vector<int>> way{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, 0)));
        // 根据base case填写初始值
        // 没有越界的所有0层都为1
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                dp[i][j][0] = 1;
            }
        }
        // 越界部分都是0
        // 任意位置只依赖下一层的某个位置，所以从下往上填
        for (int step = 1; step <= k; ++step)
        {
            for (int startx = 0; startx < m; ++startx)
            {
                for (int starty = 0; starty < n; ++starty)
                {
                    // 遍历四个方向
                    for (int i = 0; i < way.size(); ++i)
                    {
                        int curx = startx + way[i][0], cury = starty + way[i][1];
                        if (curx >= 0 && curx < m && cury >= 0 && cury < n)
                        {
                            dp[startx][starty][step] += dp[curx][cury][step - 1];
                        }
                    }
                }
            }
        }
        // 判断初始位置是否已经不在范围内
        if (x < 0 || y < 0 || x >= m || y >= n)
            return 0;
        // 返回x,y出发步数为k的值
        return dp[x][y][k] / count;
    }

private:
    // 暴力递归，三维依赖
    static int process_1(int startx, int starty, int step, int &m, int &n)
    {
        if (step == 0) // 已经无法移动了
        {
            // 判断当前位置是否是在范围内
            if (startx >= 0 && starty >= 0 && startx < m && starty < n)
                return 1; // 没有越界，存活的移动方案
            else
                return 0; // 不在范围内，死亡
        }
        // step大于0，还可以移动，Bob可以向四个方向等概率移动
        return process_1(startx + 1, starty, step - 1, m, n) +
               process_1(startx - 1, starty, step - 1, m, n) +
               process_1(startx, starty + 1, step - 1, m, n) +
               process_1(startx, starty - 1, step - 1, m, n);
    }
    // 记忆搜索
    static int process_2(int startx, int starty, int step, int &m, int &n, vector<vector<vector<int>>> &dp)
    {
        if (startx >= 0 && starty >= 0 && startx < m && starty < n)
        {
            if (dp[startx][starty][step] != -1)
                return dp[startx][starty][step];
            else if (step == 0)
            {
                dp[startx][starty][step] = 1;
            }
            else // 没越界，还能移动
            {
                dp[startx][starty][step] = process_1(startx + 1, starty, step - 1, m, n) +
                                           process_1(startx - 1, starty, step - 1, m, n) +
                                           process_1(startx, starty + 1, step - 1, m, n) +
                                           process_1(startx, starty - 1, step - 1, m, n);
            }
            return dp[startx][starty][step];
        }
        else // 越界
        {
            return 0;
        }
    }
};

void comparetest(int n)
{
    srand((unsigned)time(0));
    for (int i = 0; i < n; ++i)
    {
        int m = rand() % 10;
        int n = rand() % 10;
        int step = rand() % 5;
        int startx = rand() % 10;
        int starty = rand() % 10;
        int a = Bob::rate_1(m, n, startx, starty, step);
        int b = Bob::rate_2(m, n, startx, starty, step);
        int c = Bob::rate_3(m, n, startx, starty, step);

        if (a != b || a != c)
        {
            cout << "发生错误！" << endl;
            cout << "step:" << step << ",startx:" << startx << ",starty:" << starty << endl;
            cout << "暴力递归：" << a << endl;
            cout << "记忆搜索：" << b << endl;
            cout << "严格表结构：" << c << endl;
            return;
        }
    }
    cout << n << "组数据，测试成功！" << endl;
}

int main()
{
    cout << "计算存活率-动态规划测试" << endl;
    comparetest(10000);
    return 0;
}
