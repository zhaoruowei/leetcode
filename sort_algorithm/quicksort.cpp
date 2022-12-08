#include <iostream>
#include <vector>
using namespace std;

class sortalgorithm
{
public:
    void quicksort(vector<int>& nums)
    {
        int n = nums.size();
        if (n < 2)
        {
            return;
        }
        // 随机数种子
        srand((unsigned int)time(0));
        int L = 0, R = n-1;
        process(nums, L, R);
    }
private:
    void process(vector<int>& nums, int L, int R)
    {
        if (L < R)
        {
            // 确定随机数([L, R])
            int index = rand() % (R-L+1) + L;
            // 将index位元素与右边界元素交换，交换后的右边界元素作为索引
            myswap(nums[R], nums[index]);
            // 区间元素做partition，确定等于index的左边界和右边界
            vector<int> res(2);
            res = partition(nums, L, R);
            // 等于index的左边界作为R进行左侧递归
            process(nums, L, res[0]-1);
            // 等于index的右边界作为L进行右侧递归
            process(nums, res[1]+1, R);
        }
    }
    vector<int> partition(vector<int>& nums, int L, int R)
    {
        // 初始化小于区右边界，和大于区左边界
        int less = L-1;
        int more = R;
        // 遍历L-R区间(L指针到达大于区左边界停止)
        while (L < more)
        {
            if (nums[L] == nums[R]) // 当前元素等于index，跳过该元素
            {
                L++;
            }
            else if (nums[L] < nums[R]) // 当前元素小于index，当前元素与小于区右边界+1位置交换，小于区右边界右移
            {
                myswap(nums[++less], nums[L++]);
            }
            else // 当前元素大于index，当前元素与大于区左边界-1位置交换，大于区左边界左移
            {
                myswap(nums[--more], nums[L]);
            }
        }
        myswap(nums[L], nums[R]);
        // 返回等于区左边界，和大于区右边界
        return {less+1, more};
    }
    void myswap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
};
 
int main()
{
    vector<int> p{2,5,8,0,1,3,4,7,9,6};
    sortalgorithm test;
    test.quicksort(p);
    for (int i = 0; i < p.size(); ++i)
    {
        cout << p[i] << endl;
    }
    return 0;
}
