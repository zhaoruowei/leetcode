/*
自定义图结构，将题中给出的图结构转换为当前结构，用当前结构解题
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// 声明
class Node;
class Edge;
class Graph;

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

// 图结构
class Graph
{
public:
    unordered_map<int, Node*> nodes; // 图中的所有点集，int为编号，Node*为点的指针
    unordered_set<Edge*> edges; // 图中的所有边集合，Edge*为边的指针
    Graph()
    {}
    ~Graph()
    {
        // 删除所有点
        for (auto [_1, node] : nodes)
        {
            if (node) delete node;
        }
        // 删除所有边
        for (auto edge : edges)
        {
            if (edge) delete edge;
        }
    }
public:
    // 宽度优先遍历
    void BFS(Node* node)
    {
        if (!node)
        {
            return;
        }
        
        queue<Node*> list;
        unordered_set<Node*> visited;
        list.emplace(node);
        visited.emplace(node);
        
        while (!list.empty())
        {
            Node* cur = list.front();
            list.pop();
            // 打印当前结点
            cout << cur->val << endl;
            // 查找与当前点相连的所有点
            for (auto n : cur->nexts)
            {
                // 如果n没有访问过则加入队列，否则跳过
                if (visited.find(n) == visited.end())
                {
                    list.emplace(n);
                    visited.emplace(n);
                }
            }
        }
    }
    // 深度度优先遍历
    void DFS(Node* node)
    {
        if (!node)
        {
            return;
        }
        stack<Node*> list;
        unordered_set<Node*> visited;
        list.emplace(node);
        visited.emplace(node);
        // 结点入栈时打印
        cout << node->val << endl;
        while (!list.empty())
        {
            Node* cur = list.top();
            list.pop();
            // 查找与当前点相连的所有点
            for (auto n : cur->nexts)
            {
                // 如果没有访问过就将当前点，和相连的点先后入栈，便于回溯
                if (visited.find(n) == visited.end())
                {
                    list.emplace(cur);
                    list.emplace(n);
                    visited.emplace(n);
                    // 打印相连点
                    cout << n->val << endl;
                    // 结束遍历
                    break;
                }
            }
        }
    }
    // 拓扑排序，有向图中按拓扑（依赖关系）输出所有的点
    vector<Node*> sortTopology(Graph* graph)
    {
        // 存储结果
        vector<Node*> ans;
        
        // 将图中的所有点作为key,入度作为value存入hashmap
        unordered_map<Node*, int> hashmap;
        queue<Node*> zeroInQueue; // 入度为0的点才能入队列
        
        // 遍历图中的所有点
        for (auto [_1, node] : graph->nodes)
        {
            // 找到入度为0的点入队
            if (!node->in)
            {
                zeroInQueue.emplace(node);
            }
            else
            {
                hashmap.emplace(node, node->in); // 将入度不为0的点放入hashmap
            }
        }
        
        // 依次弹出队列中的点
        while (!zeroInQueue.empty())
        {
            Node* curnode = zeroInQueue.front();
            zeroInQueue.pop();
            // 保存弹出的点的信息
            ans.emplace_back(curnode);
            // 遍历所有与当前点相关的点
            for (auto node : curnode->nexts)
            {
                // 所有遍历到的点的入度--
                hashmap[node]--;
                // 如果入度为0入队
                if (hashmap[node] == 0)
                {
                    zeroInQueue.emplace(node);
                }
            }
        }
        return ans;
    }
    // 最小生成树，kruskal算法,适用于无向图
    vector<Edge*> kruskalMST(Graph* graph)
    {
        vector<Edge*> ans;
        // 使用优先级队列，自定义比较函数，将所有边按权值大小放入优先级队列中，每次取权值最小的边
        priority_queue<Edge*, vector<Edge*>, mycmp> edgequeue;
        // 遍历所有边，加入小顶堆
        for (auto edge : graph->edges)
        {
            edgequeue.push(edge);
        }
        // 构建点的并查集,将所有点创建一个集合
        UnionFindeSet* uset = new UnionFindeSet(graph);
        // 从小顶堆中遍历所有边
        while (!edgequeue.empty())
        {
            Edge* curedge = edgequeue.top();
            edgequeue.pop();
            // 找到当前边对应的两点
            Node* from = curedge->from;
            Node* to = curedge->to;
            // 判断两点是否是一个集合
            if (!uset->isSameSet(from, to))
            {
                // 合并两点所在的集合
                uset->unionSet(from, to);
                // 记录当前边
                ans.emplace_back(curedge);
            }
        }

        return ans;
    }
private:
    // 并查集结构
    class UnionFindeSet
    {
    public:
        unordered_map<Node*, unordered_set<Node*>*> nodesetmap; // 记录每一个点所在的集合
        vector<unordered_set<Node*>*> sets; // 存储所有的点集合，用于析构
        UnionFindeSet(Graph* graph) // 构造，将所有点放到各自的集合中
        {
            // 遍历图中所有的点
            for (auto [_1, node] : graph->nodes)
            {
                // 每个点创建一个新集合，并相互对应
                unordered_set<Node*>* newset = new unordered_set<Node*>;
                // 将创建的set与node一一绑定
                nodesetmap.emplace(node, newset);
                // 将创建的新set放入sets，便于析构
                sets.emplace_back(newset);
            }
        }
        ~UnionFindeSet()
        {
            for (auto newset : this->sets)
            {
                if(newset) delete newset;
            }
        }
    public:
        // 查询点是否在一个集合中
        bool isSameSet(Node* from, Node* to)
        {
            // 在map中分别找到两个点的set地址
            unordered_set<Node*>* fromset = this->nodesetmap[from];
            unordered_set<Node*>* toset = this->nodesetmap[to];
            return fromset == toset;
        }
        // 合并两个所在的set
        void unionSet(Node* from, Node* to)
        {
            // 在map中分别找到两个点的set地址
            unordered_set<Node*>* fromset = this->nodesetmap[from];
            this->nodesetmap[to] = fromset;
        }
    };

    // 边的小顶堆
    struct mycmp
    {
        bool operator()(Edge* edge1, Edge* edge2)
        {
            return edge1->weight > edge2->weight;
        }    
    };
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
    // 宽度优先遍历
    // graph->BFS(graph->nodes[0]);
    // 深度优先遍历
    // graph->DFS(graph->nodes[0]);
    vector<Edge*> ans = graph->kruskalMST(graph);
    for (auto edge : ans)
    {
        cout << edge->weight << endl;
    }
    
    
    if (graph) delete graph;
    
    return 0;
}
