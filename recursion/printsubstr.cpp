/*
打印字符串str的所有子串，包括空串
str = ‘abc’,三个char每一个右两种状态，即要或者不要
遍历每一个字符，有两种选择，保留当前子串进行递归，不保留当前子串进行递归
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class sloution
{
public:
    vector<string> printsubstr(string word)
    {
        vector<string> ans;
        int length = word.length();
        if (length < 1) return ans;
        // 从第0个字符开始递归
        string res; // 每一种可能的字符串 
        // process1(0, res, word, ans);
        process2(0, word, ans);
        return ans;
    }
private:
    void process1(int i, string& res, string word, vector<string>& ans)
    {
        if (i >= word.length()) // 已经遍历完所有字符，结算，返回
        {
            ans.emplace_back(res); // 结算，0-n-1记录
            return;
        }
        // 当前第i个字符的操作
        // 取出当前i位置的字符
        char cur = word[i];
        // 选择要或者不要进行递归
        // 1.要当前字符
        res.push_back(cur);
        // 将i层组装好的string带到i+1层递归
        process1(i+1, res, word, ans);
        // 返回第i层，选择不要当前字符递归,清除这层添加的字符
        res.pop_back();
        // 再次递归
        process1(i+1, res, word, ans);
    }
    // 将word当作数组，到达第i层时直接修改当前字符的值
    void process2(int i, string word, vector<string>& ans)
    {
        if (i >= word.length())
        {
            ans.emplace_back(word);
            return;
        }
        // 第i层的选择, 要当前层字符
        process2(i+1, word, ans);
        // 第i层选择不要当前层
        char temp = word[i];
        word.replace(i, 1, "0"); // 不选择，空字符用0代替
        process2(i+1, word, ans);
        // 恢复字符串
        word.replace(i, i, 1, temp);
    }
};

void testprintsubstr(string word)
{
    sloution s;
    vector<string> ans = s.printsubstr(word);
    cout << "所有子串个数为：" << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i)
    {
        cout << i+1 << "  :" << ans[i] << endl;
    }
}

int main()
{
    cout << "暴力递归-打印字符串所有子串" << endl;
    string word;
    cout << "输入测试字符串：";
    cin >> word;

    testprintsubstr(word);

    return 0;
}
