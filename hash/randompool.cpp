/*
一种结构，实现三种功能
insertKey(key):插入一个新key，底层不出现重复
deleteKey(key):删除一个已有的key
getRandom():等概率的返回一个存储的key
*/

#include <iostream>
#include <unordered_map>
#include <ctime>

using namespace std;

class RandomPool
{
public:
    unordered_map<char, int> keyindexmap; // 存储key加入的顺序，char为输入的key，index为加入的顺序1-26
    unordered_map<int, char> indexkeymap; // 存储key的索引，key为加入的char，index为加入的顺序，即将keyindexmap的key，value反转
    int index;
    RandomPool(): index(0)
    {
        srand((unsigned int)time(0)); // 生成随机数种子
    }; // 初始化下标，当前无key
public:
    // 插入key
    void insertKey(char key)
    {
        if (keyindexmap.find(key) != keyindexmap.end()) return; // 已加入的不更新
        // 将当前index作为key，cahr作为value插入.插入后index++
        this->keyindexmap.emplace(key, ++index);
        this->indexkeymap.emplace(index, key); // 表明1号位为key
    }
    // 删除key
    void deleteKey(char key)
    {
        // 1-index随机取一个数很容易实现，但是如果直接删除一个key，这个key正好位于1-index区间内
        // 那么删除key后，会导致1-index区间不再是连续的，将无法实现随机取数，如果正好宣导删除的key的索引，将无法找到key
        // 所以要实现，删除某一个key后，用其他位置的key来填补删除的漏洞
        if (this->keyindexmap.find(key) == this->keyindexmap.end())
        {
            cout << "删除的key不存在结构中" << endl;
            return;
        }

        int i = this->keyindexmap[key]; // 找到要删除的key的索引

        this->keyindexmap[key] = this->index;
        char temp = this->indexkeymap[index];
        this->keyindexmap[temp] = i;
        this->indexkeymap[i] = this->indexkeymap[index];
        this->keyindexmap.erase(this->keyindexmap.find(key));
        this->indexkeymap.erase(this->indexkeymap.find(index--));
    }
    // 等概率获得key
    char getRandom()
    {
        if (this->index == 0) return 0;
        // key为26个小写字母，所以随机选择1-26中的任意一个数，实现随机选择
        // 当前map中可能只有index个key
        int i = rand() % index + 1; // 1-index随机选择一个数字
        return indexkeymap[i]; // 返回随机的key
    }
};


int main()
{
    cout << "字符型RandomPool结构-key均为小写字母" << endl;
    RandomPool rp;
    rp.insertKey('a');
    rp.insertKey('b');
    rp.insertKey('a');
    rp.insertKey('c');
    rp.insertKey('d');
    rp.insertKey('g');
    rp.insertKey('o');
    rp.insertKey('p');
    rp.insertKey('e');
    rp.insertKey('r');
    rp.insertKey('w');
    rp.insertKey('q');
    cout << rp.getRandom() << endl;
    cout << rp.getRandom() << endl;
    cout << rp.getRandom() << endl;
    rp.deleteKey('f');
    rp.deleteKey('a');
    cout << rp.getRandom() << endl;
    cout << rp.getRandom() << endl;
    cout << rp.getRandom() << endl;

    return 0;
}
