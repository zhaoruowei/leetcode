class sloution
{
public:
    // n层汉诺塔移动
    vector<string> hanota(int n)
    {
        // 左中右三个柱子
        // 1.移动第i层时，需要把之前的0-i-1层移动到中间柱上
        // 2.把当前层移动到右柱子上
        // 3.把0-i-1层移到右柱子上
        // 从第i层开始递归
        // 保存每次移动的操作
        vector<string> ans;
        if (n < 1) return ans;
        int i = n; // 把最后一层从左移到右
        // 用string表示柱子
        string left = "左";
        string mid = "中";
        string right = "右";
        // 将第n层，从左移到右
        cout << process(i, left, right, mid, ans) << endl;
        return ans;
    }
private:
    int process(int i, string from, string to, string other, vector<string>& ans)
    {
        // 终止条件当i==0表示已经没有可以移动的层了终止
        if (i == 0)
        {
            return 0;
        }
        // 记录已经移动的次数（当前层算1次）
        int count = 1;
        // 本层需要的操作
        // 1.将i-1层移动到other
        count += process(i-1, from, other, to, ans);
        // 2.将i层从from移到to
        string res = "移动"+to_string(i)+"从"+from+"到"+to; // 记录本层的操作
        ans.emplace_back(res);
        // 3.将i-1层从other移动到to
        count += process(i-1, other, to, from, ans);
        return count;
    }
};
