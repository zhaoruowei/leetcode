/*
    中国象棋中棋盘的大小为10*9，马可以跳日子，规定马从0，0位置出发，必须跳k次，问最终来到x,y位置有多少种跳法
*/

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Chess
{
public:
    // 暴力递归，三维位置依赖
    static int getWays_1(int k, int x, int y)
    {
        return process_1(0, 0, k, x, y); // 从0，0位置跳，跳k次到达x，y
    }
    // 记忆搜索
    static int getWays_2(int k, int x, int y)
    {
        vector<vector<vector<int>>> dp(10, vector<vector<int>>(9, vector<int>(k + 1, -1)));
        return process_2(0, 0, k, x, y, dp);
    }
    // 严格表结构，三维依赖
    // 根据位置依赖关系，与题意解耦，三个变量，看作三维空间
    static int getWays_3(int k, int x, int y)
    {
        vector<vector<vector<int>>> dp(10, vector<vector<int>>(9, vector<int>(k + 1, 0)));
        // 八个方向的数组
        vector<vector<int>> way{{-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}};
        // 根据base case填充初始值
        // 第一层k为0时，除了x，y位置都是0
        dp[x][y][0] = 1;
        // 根据递归依赖关系，任一层的任一点都依赖下层的数据，所以选择从下往上填的顺序
        // 越界位置的返回值都是0
        for (int step = 1; step <= k; ++step)
        {
            for (int startx = 0; startx < 10; ++startx)
            {
                for (int starty = 0; starty < 9; ++starty)
                {
                    // 遍历8个方向的值
                    for (int i = 0; i < way.size(); ++i)
                    {
                        int x = startx + way[i][0], y = starty + way[i][1];
                        if (x >= 0 && y >= 0 && x < 10 && y < 9)
                        {
                            dp[startx][starty][step] += dp[x][y][step - 1];
                        }
                    }
                }
            }
        }

        // 输出第k层，0，0坐标的值
        return dp[0][0][k];
    }

private:
    // 暴力递归
    static int process_1(int startx, int starty, int step, int &endx, int &endy)
    {
        if (startx < 0 || starty < 0 || startx >= 10 || starty >= 9) // 棋子出界，方法无效
        {
            return 0;
        }
        // 棋子未出界，step==0, 判断是否来到终止位置
        if (step == 0) // 无法移动
        {
            return (startx == endx) && (starty == endy) ? 1 : 0;
        }
        // 还可以移动，选择下次移动的8个方向，求每个选择的结果之和
        return process_1(startx - 1, starty + 2, step - 1, endx, endy) +
               process_1(startx - 2, starty + 1, step - 1, endx, endy) +
               process_1(startx - 2, starty - 1, step - 1, endx, endy) +
               process_1(startx - 1, starty - 2, step - 1, endx, endy) +
               process_1(startx + 1, starty - 2, step - 1, endx, endy) +
               process_1(startx + 2, starty - 1, step - 1, endx, endy) +
               process_1(startx + 2, starty + 1, step - 1, endx, endy) +
               process_1(startx + 1, starty + 2, step - 1, endx, endy);
    }
    static int process_2(int startx, int starty, int step, int &endx, int &endy, vector<vector<vector<int>>> &dp)
    {
        if (startx < 0 || starty < 0 || startx >= 10 || starty >= 9) // 棋子出界，方法无效
        {
            return 0;
        }
        if (dp[startx][starty][step] != -1)
        {
            return dp[startx][starty][step];
        }
        if (step == 0)
        {
            dp[startx][starty][step] = (startx == endx && starty == endy) ? 1 : 0;
        }
        else
        {
            dp[startx][starty][step] = process_1(startx - 1, starty + 2, step - 1, endx, endy) +
                                       process_1(startx - 2, starty + 1, step - 1, endx, endy) +
                                       process_1(startx - 2, starty - 1, step - 1, endx, endy) +
                                       process_1(startx - 1, starty - 2, step - 1, endx, endy) +
                                       process_1(startx + 1, starty - 2, step - 1, endx, endy) +
                                       process_1(startx + 2, starty - 1, step - 1, endx, endy) +
                                       process_1(startx + 2, starty + 1, step - 1, endx, endy) +
                                       process_1(startx + 1, starty + 2, step - 1, endx, endy);
        }
        return dp[startx][starty][step];
    }
};

void comparetest(int n)
{
    srand((unsigned)time(0));
    for (int i = 0; i < n; ++i)
    {
        int step = rand() % 10;
        int endx = rand() % 10;
        int endy = rand() % 9;
        int a = Chess::getWays_1(step, endx, endy);
        int b = Chess::getWays_2(step, endx, endy);
        int c = Chess::getWays_3(step, endx, endy);
        if (a != b || a != c)
        {
            cout << "发生错误！" << endl;
            cout << "step:" << step << ",endx:" << endx << ",endy:" << endy << endl;
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
    cout << "象棋游戏-动态规划测试" << endl;
    comparetest(10000);
    return 0;
}
