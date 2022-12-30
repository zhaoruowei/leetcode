/*
不使用+，-，*，/，仅仅使用位运算实现加减乘除
^:无进位相加
&:需要进位的位，<<后完成进位
正数保存的时原码，负数保存的是补码
正负数的切换： n ==> (~n+1)
取出最低位的数 n & 1 ===》 循环取出最低位 while (n!=0) lowbit = n&1; n = n>>1;
无符号右移，n = (unsigned int)n >> 1;高位补0
*/

#include <iostream>
#include <ctime>

using namespace std;

class BitCalculate
{
public:
    int add(int a, int b)
    {
        // a ^ b 得到无进位相加结果
        // (a & b) << 1 得到进位后的结果
        // (a ^ b) 与 ((a & b) << 1) 再计算 ^ 与 & << 当&后的结果为0时退出
        int sum = a;
        while (b != 0)
        {
            a = sum ^ b;
            b = (sum & b) << 1;
            sum = a;
        }
        return sum;
    };
    int minus(int a, int b)
    {
        // a - b == a + (-b) == a + (~b+1)
        return add(a, add(~b, 1));
    };
    int times(int a, int b)
    {
        // 乘法，每一个bit相乘，移位相加
        int sum = 0;
        while (b != 0)
        {
            if ((b & 1) == 1) // 最低位是1
            {
                sum = add(sum, a);
            }
            b = (unsigned int)b >> 1;
            a = a << 1;
        }
        return sum;
    }
    int divided(int a, int b)
    {
        if (a == 0) return 0;
        if (b == 0) return INT_MIN; // 不合法
        int signa = ((a >> 31) & 1); // 获取a的符号位，0为正数，1为负数
        int signb = ((b >> 31) & 1); // 获取b的符号位，0为正数，1为负数
        // 将负数变为正数
        a = signa ? add(~a, 1) : a;
        b = signb ? add(~b, 1) : b;

        // 利用减法实现
        int sum = 0;
        for (int i = 31; i > -1; i = add(i, add(~1, 1)))
        {
            if ((a >> i) >= b)
            {
                a = add((a >> i), add(~b, 1));
                sum = add(sum, (1 << i));
            }
        }

        return (signa == signb) ? sum : add(~sum, 1);
    }
};

int main()
{
    cout << "位运算-实现算术运算" << endl;
    srand((unsigned int)time(0));
    BitCalculate bitcal;
    int a = rand() % INT_MAX, b = rand() % INT_MAX;
    // a = 27; b = -6;
    cout << a << " + " << b <<" = " << bitcal.add(a, b) << " == " << (a+b) << endl;
    cout << a << " - " << b <<" = " << bitcal.minus(a, b) << " == " << (a-b) << endl;
    cout << a << " * " << b <<" = " << bitcal.times(a, b) << " == " << (a*b) << endl;
    cout << a << " / " << b <<" = " << bitcal.divided(a, b) << " == " << (a/b) << endl;
    return 0;
}
