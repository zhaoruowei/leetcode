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
public:
    // 利用位运算降低常树时间，不能超过32皇后，int32位
    vector<vector<string>> solveNQueens2(int n)
    {
        // 保存所有可行的结果集合
        vector<vector<string>> ans;
        // 函数边界值检查
        if (n < 1 || n > 32)
        {
            return ans;
        }

        // 定义每一行摆放的初始结构res,初始每一行都是空位，即全是'.'
        string res;
        for (int i = 0; i < n; ++i)
        {
            res.push_back('.');
        }
        // 保存每一层的摆放结果，如果n个字符串都能摆上Q，就是一种可行的摆放方案，存入ans中
        vector<string> record(n, res); // 存放的string是每一层的结果，初始共n个res

        // 使用整数的二进制数记录Q的摆放
        // 取一个32整数的二进制表达形式，即32个1，n皇后就是低位的n个位置为0，其他高位为1，0位置表示可以存放Q
        // n为32时，32位都为0，都可以摆放
        // 当n == 8时，1为0000,0000,0000,0000,0000,0000,0000,0001 左移n位相当于低位的n个位置为0
        // 0000,0000,0000,0000,0000,0001,0000,0000  -1等于+(-1)
        // 1111,1111,1111,1111,1111,1111,1111,1111
        // 0000,0000,0000,0000,0000,0000,1111,1111
        // 当n=32时，limit为-1，即1111,1111,1111,1111,1111,1111,1111,1111
        // 表示初始的限制，1位不能摆放Q
        int limit = n == 32 ? -1 : (1 << n) - 1;
        // 调用递归函数从第row行开始摆放Q
        // limit为初始的棋盘，collimit,leftlimit,rightlimit分别表示列限制，左斜线限制，右斜线限制
        // 初始第一行可以在任意列摆放，所以所有限制都是0
        cout << process2(limit, 0, 0, 0, 0, n, record, ans) << endl;

        return ans;
    }
private:
    // 利用位运算降低常数时间
    int process2(int limit, int collimit, int leftlimit, int rightlimit, int row, int n, vector<string>& record, vector<vector<string>>& ans)
    {
        // limit为限制，二进制为1的位置不能摆Q，为0的才可以摆放
        // 每行的摆放结果将是一个二进制数，1位置为摆放的位置
        // 如果列限制和limit相等，即任何一列都不能摆放Q时，退出，结算
        if (collimit == limit) // collimit = 为n个1
        {
            ans.emplace_back(record);
            return 1;
        }

        // 记录当前层可行的方案次数
        int count = 0;

        // 根据4个limit算出当前行可以填Q的位置
        int rowlimit = (collimit | leftlimit | rightlimit); // 只要有为1的位置就为1，不能填Q，1110，0000
        int pos = limit & ~(rowlimit); // 得到该层所有可以填Q的位置，0001，1111
        // 依次取最右边的1，进行下一层递归
        while (pos != 0) // 没有取完1
        {
            int mostRightone = pos & (~pos+1); // 0000,0001,最右边的1，就是这次遍历到的可以放Q的位置, 每次递归当前层都会改变most的值
            pos = pos - mostRightone; // 1111,1110当前行的摆放结果

            // 将mostRightone位的.修改为Q，0000，0001转变为7:0000,0111
            // 找出1在mostRightone的第几位，mostRightone右移m位等于0
            int temp = mostRightone;
            int m = 0;
            while (temp)
            {
                temp = temp >> 1;
                ++m;
            }

            record[row][n-m] = 'Q';

            // 算出下一行的限制，进行下一行的递归
            count += process2(limit, (collimit | mostRightone), (leftlimit | mostRightone) << 1, (rightlimit | mostRightone) >> 1, row+1, n, record, ans);

            // 重置当前行在record中的记录
            // 将mostRightone位的.修改为.
            record[row][n-m] = '.';
        }
        return count;
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
    // 打印结果
    printAns(ans);
    // cout.precision(6);
    cout << "process1函数运行时间为：" << ((double)(end.QuadPart-start.QuadPart)/(double)tc.QuadPart)*1000 << "ms" << endl;
}

void testNQueenProcess2(int n)
{
    sloution s;
    vector<vector<string>> ans;
    cout << n << "Q test:";
    cout << "函数输出结果个数：";
    // 计时
    LARGE_INTEGER start, end, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start);
    ans = s.solveNQueens2(n);
    QueryPerformanceCounter(&end);
    // 打印结果
    printAns(ans);
    // cout.precision(6);
    cout << "process2函数运行时间为：" << ((double)(end.QuadPart-start.QuadPart)/(double)tc.QuadPart)*1000 << "ms" << endl;
}

int main()
{
    cout << "N皇后问题测试" << endl;
    
    testNQueenProcess1(5);

    cout << "=================================" << endl;

    testNQueenProcess2(5);
    
    return 0;
}
