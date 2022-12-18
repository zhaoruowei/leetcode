/*
自定义图结构，将题中给出的图结构转换为当前结构，用当前结构解题
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// 声明
class Node;
class Edge;
class Graph;

// 图结构
class Graph
{
public:
    unordered_map<int, Node*> nodes; // 图中的所有点集，int为编号，Node*为点的指针
    unordered_set<Edge*> edges; // 图中的所有边集合，Edge*为边的指针
    Graph()
    {}
};

// 点结构
class Node
{
public:
    int val; // 点的权值
    int in; // 点的入度（指向该点的边有几条）
    int out; // 点的出度(从该点出发的边有几条)
    vector<Node*> nexts; // 与该点直接相连的点的指针
    vector<Edge*> edges; // 与该点直接相连的边的指针
    Node(int val, int in, int out)
    {
        this->val = val;
        this->in = in;
        this->out = out;
    }
};

// 边结构
class Edge
{
public:
    int weight; // 边的权值
    Node* from; // 边的出发点
    Node* to; // 边的目的点
    Edge(int weight, Node* from, Node* to)
    {
        this->weight = weight;
        this->from = from;
        this->to = to;
    }
};

void inputData(int n, vector<vector<int>>& matrix)
{
    int m = 0;
    cout << "输入矩阵行数：" << endl;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        vector<int> res;
        for (int j = 0; j < n; ++j)
        {
            int temp;
            cout << "输入第" << i+1 << "行，" << "第" << j+1 << "个值：" << endl;
            cin >> temp;
            res.emplace_back(temp);
        }
        matrix.emplace_back(res);
    }
}

void outputData(vector<vector<int>>& matrix)
{
    int m = matrix.size();
    if (m < 1)
    {
        return;
    }
    int n = matrix[0].size();
    
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << matrix[i][j] << endl;
        }
    }
}

Graph* vectortoGraph(vector<vector<int>>& matrix)
{
    Graph* newGraph = new Graph;
    
    int m = matrix.size();
    if (m < 1)
    {
        return newGraph;
    }
    int n = matrix[0].size();
    
    for (int i = 0; i < m; ++i)
    {
        // 取出每行数据的三个元素
        int edgeWeight = matrix[i][0]; // 边的权值
        int nodefrom = matrix[i][1]; // 出发点的编号
        int nodeto = matrix[i][2]; // 目标点的编号
        // 先处理点,如果点不在图的点集中就创建点
        if (newGraph->nodes.find(nodefrom) == newGraph->nodes.end())
        {
            // 创建新点，将点加入图
            newGraph->nodes.emplace(nodefrom, new Node(nodefrom, 0, 0));
        }
        if (newGraph->nodes.find(nodeto) == newGraph->nodes.end())
        {
            newGraph->nodes.emplace(nodeto, new Node(nodeto, 0, 0));
        }
        // 取出当前行对应的两个点
        Node* fromnode = newGraph->nodes[nodefrom];
        Node* tonode = newGraph->nodes[nodeto];
        // 创建边
        Edge* edge = new Edge(edgeWeight, fromnode, tonode);
        // 将边加入图
        newGraph->edges.emplace(edge);
        // 修改两个点的nexts数组
        fromnode->nexts.emplace_back(tonode);
        // 两个点的出入度增加
        fromnode->out++;
        tonode->in++;
        // 将边加入点
        fromnode->edges.emplace_back(edge);
        tonode->edges.emplace_back(edge);
    }
    
    
    return newGraph;
}

int main()
{
    // 示例1，一个二维矩阵matrix，matrix的每一行有三个元素
    // 每一行的三个元素分别表示，指向两个点的权值，点1，点2
    vector<vector<int>> matrix;
    inputData(3, matrix);
    // outputData(matrix);
    Graph* graph = vectortoGraph(matrix);
    // if (graph) delete graph;
    
    return 0;
}
