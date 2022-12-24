/*
分支限界，在递归中限制递归可能的路径，在常数时间上降低数据清洗的时间消耗
输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
比如输入abc
返回abc,acb,bca,bac,cab,cba
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class sloution
{
public:
    vector<string> sortallchar(string word)
    {
        vector<string> ans;
        int length = word.length();
        if (length < 1) return ans;

        process(0, length, word, ans);
        return ans;
    }
private:
    void process(int i, int length, string& word, vector<string>& ans) // 考虑当前位置可以选的字符，0-i-1已经确定
    {
        if (i == length) // 到达字符串尾部，结算退出
        {
            ans.emplace_back(word);
            return;
        }
        vector<int> visitedchar(26, 0); // 记录当前层已经选择过的字符
        // 拼装的字符的第j位可以选择i到length上的任意一个字符
        for (int j = i; j < length; ++j)
        {
            // 如果当前字符没有在数组中标记过，即当前位置没有选过这个字符
            if (visitedchar[word[j]-'a'] == 0)
            {
                // 第i位与第j位交换，修改数组
                visitedchar[word[j]-'a'] = 1;
                swap(word[j], word[i]);
                process(i+1, length, word, ans);
                // 返回当层重置word
                swap(word[i], word[j]);
            }
        }
    }
};

int main()
{
    cout << "暴力递归-打印字符串所有排列" << endl;
    string word = "abb";
    sloution s;
    vector<string> ans = s.sortallchar(word);
    for (int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << endl;
    }

    return 0;
}
