/*
一个字符串型数组中有n个字符串
如何将所有n个字符串合并后得到的字典序最小？
arr["abc", "cx", "gf", "ewq"]
策略：选择字符a和字符b，判断a+b与b+a的大小，选择字典序小的拼接方法
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class sloution
{
public:
    string getloweststring(vector<string> data)
    {
        int n = data.size();
        if (n < 1)
        {
            return "";
        }
        // 按两个字符串拼接升序排列数组
        sort(data.begin(), data.end(), cmp);
        // 遍历排序后的数组拼接新字符串
        string ans;
        for (int i = 0; i < n; ++i)
        {
            // printdata(data[i]);
            ans.append(data[i]);
        }
        return ans;
    }
private:
    void printdata(string word)
    {
        cout << word << endl;
    }
    // sort调用类中的比较函数需要使用static静态函数，应为sort底层调用时找不到具体的类对象
    static bool cmp(string a, string b)
    {   
        // a+b <= b+a时，compare返回0，-1
        if ((a+b).compare(b+a) == 1) return true;
        else return false;
    }
    struct mycmp
    {
        bool operator()(string a, string b)
        {
            if ((a+b).compare(b+a) < 1) return true;
            else return false;
        }
    };
};

int main()
{
    cout << "字符串拼接贪心算法测试" << endl;
    vector<string> testdata{"a", "xc", "bf", "cfsds", "abv", "st"};
    sloution s;
    cout << s.getloweststring(testdata) << endl;
    // string a = "hello";
    // string b = "world";
    // // 字符串比较 a = b 返回0， a<b返回-1，a>b返回1
    // cout << (a+b).compare(b+a) << endl;
    return 0;
}
