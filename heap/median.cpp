/*
用户不断的输入数字，实现同步返回数字串的中位数
*/

#include <iostream>
#include <queue>

using namespace std;

class sloution
{
public:
    priority_queue<int, vector<int>, greater<int>> heapmin; // 小顶堆
    priority_queue<int, vector<int>, less<int>> heapmax; // 大顶堆
public:
    void insertnum(int n)
    {
        // 如果大根堆没有元素，或者当前新元素小于大根堆堆顶
        if (this->heapmax.empty() || n < this->heapmax.top())
        {
            // 元素进大根堆
            this->heapmax.emplace(n);
        }
        else // 当前元素大于等于大根堆堆顶
        {
            this->heapmin.emplace(n);
        }
        // 如果两个根堆的元素个数差值大于1，将多的堆的堆顶，弹入少的堆中
        // 获取大小根堆的数据量
        int min = this->heapmin.size();
        int max = this->heapmax.size();
        while (abs(max-min) > 1)
        {
            if (max > min)
            {
                this->heapmin.emplace(this->heapmax.top());
                this->heapmax.pop();
            }
            else
            {
                this->heapmax.emplace(this->heapmin.top());
                this->heapmin.pop();
            }
            min = this->heapmin.size();
            max = this->heapmax.size();
        }
    }
    int getmedian()
    {
        int min = this->heapmin.size(); // 小堆大小
        int max = this->heapmax.size(); // 大堆大小
        int res = max-min;

        if (res > 0) // 大堆多
        {
            return this->heapmax.top();
        }
        else if (res < 0) // 小堆多
        {
            return this->heapmin.top();
        }
        else // 一样多（偶数个）
        {
            return (this->heapmin.top() + this->heapmax.top()) / 2;
        }
    }
};


int main()
{
    cout << "获取中位数测试" << endl;
    sloution s;
    int n;
    while (cin >> n)
    {
        s.insertnum(n);
        cout << s.getmedian() << endl;
    }

    return 0;
}
