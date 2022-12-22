/*
n皇后问题
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。不共列，不共斜线
返回可能的摆放位置，输出次数
每一行的结果用字符串表示，空位为‘.’ 皇后为‘Q’,比如“..Q..”
*/

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class sloution
{
public:
    // 主函数，确定棋盘大小为N*N
    vector<vector<string>> solveNQueens(int n)
    {
        // 保存所有可行的结果集合
        vector<vector<string>> ans;
        // 定义每一行摆放的初始结构res,初始每一行都是空位，即全是'.'
        string res;
        for (int i = 0; i < n; ++i)
        {
            res.push_back('.');
        }
        // 保存每一层的摆放结果，如果n个字符串都能摆上Q，就是一种可行的摆放方案，存入ans中
        vector<string> record(n, res); // 存放的string是每一层的结果，初始共n个res
        // 调用递归函数从第row行开始摆放Q
        int row = 0;
        cout << process1(row, n, record, ans) << endl;
        return ans;
    }
private:
    // 递归函数
    int process1(int row, int n, vector<string>& record, vector<vector<string>>& ans)
    {
        // row表示当前处理的是第几行的下标，即第row行选择列摆放Q。n是一共有多少行
        // 当row==n时表示棋盘越界，因为每一行的下标从0开始
        if (row == n)
        {
            // 递归来到最后一层，进行结算，完成一次成功的排列，返回1，存储这次排列传递下来的record结果
            ans.emplace_back(record);
            return 1;
        }
        // 记录当前层一共有集中可行的摆放方案
        int count = 0;
        // 没有到达n行，此时考虑当前行第row行的摆放位置
        // record中记录了0-row-1行的摆放位置，因为按行记录，所以不用考虑当前行是否与之前的Q共行
        // 遍历row行的每一列，判断是否合法，选择一个合法的位置记录，进行下一层的递归
        for (int col = 0; col < n; ++col)
        {
            // 检查在row,col位置摆放Q是否与之前的0-row-1行有冲突
            if (checkPos(row, col, n, record)) // 不冲突，当前列row,col可以摆放，在当前行的记录中记录位置
            {
                // row行col列，摆上Q
                record[row][col] = 'Q';
                // 进行下一行的遍历
                count += process1(row+1, n, record, ans);
                // 下一层遍历完成返回当前层，将修改的当前行的摆放记录复原
                // 继续遍历下一列，查找其他的可能方案，继续进行递归
                record[row][col] = '.';
            }
        }
        return count;
    }
    // 检查是否可以放Q
    bool checkPos(int row, int col, int n, vector<string>& record)
    {
        // 检查在第row行，第col列摆放Q是否与record记录的0-row-1行结果相冲突
        // 遍历record的已经有记录的0-row-1行
        for (int i = 0; i < row; ++i)
        {
            // 遍历record第i行的每一列，找到该列中Q的位置
            for (int j = 0; j < n; ++j)
            {
                // 找到等于Q的坐标
                if (record[i][j] == 'Q')
                {
                    // 将i行j列的Q坐标，与当前选择的row行，col列进行检查
                    // 1.是否共列
                    if (j == col) return false;
                    // 2.是否共斜线，即两点组成直线的斜率为1或-1
                    // 斜率公式为(y2-y1)/(x2-x1) == 1||-1
                    // 避免x2-x1为0，即判断abs(y2-y1) = abs(x2-x1)
                    if (abs(row-i) == abs(col-j)) return false;
                }
            }
        }
        // 通过检查1，2，返回true，row行j列可以摆Q
        return true;
    }
};

void printAns(vector<vector<string>>& ans)
{
    int n = ans.size();
    cout << "ans的个数为：" << n << endl;

    for (int i = 0; i < n; ++i)
    {
        vector<string> res = ans[i];
        cout << "第" << i+1 << "种结果：";
        for (int j = 0; j < res.size(); ++j)
        {
            cout << res[j] << ",";
        }
        cout << endl;
    }
}

void testNQueenProcess1(int n)
{
    sloution s;
    vector<vector<string>> ans;
    cout << n << "Q test:";
    cout << "函数输出结果个数：";
    // 计时
    LARGE_INTEGER start, end, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start);
    ans = s.solveNQueens(n);
    QueryPerformanceCounter(&end);
    // printAns(ans);
    // cout.precision(6);
    cout << "process1函数运行时间为：" << ((double)(end.QuadPart-start.QuadPart)/(double)tc.QuadPart)*1000 << "ms" << endl;
}

int main()
{
    cout << "N皇后问题测试" << endl;
    
    testNQueenProcess1(12);
    
    return 0;
}
