#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// 基础的邻接表图实现（有向图）
class Graph {
public:
    int V;  // 顶点数量
    vector<vector<int>> adj;  // 邻接表

public:
    // 构造函数
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // 添加边（有向图）
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // 打印邻接表
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "顶点 " << i << " 的邻接点: ";
            for (int v : adj[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};
class WeightedGraph {
public:
    int V;
    // 使用pair存储邻接点和权重
    vector<list<pair<int, int>>> adj;  // pair<顶点, 权重>

public:
    WeightedGraph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // 添加带权重的边
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({ v, weight });
    }

    // 添加无向带权边
    void addUndirectedEdge(int u, int v, int weight) {
        adj[u].push_back({ v, weight });
        adj[v].push_back({ u, weight });
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "顶点 " << i << " 的邻接点: ";
            for (auto& neighbor : adj[i]) {
                cout << "(" << neighbor.first << ", 权重:" << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};
//拓扑排序:
vector<int>postorder;
bool hasCycle = false;
vector<bool> visited, onPath;
void traverse(Graph G, int s);
vector<int>Topsort(Graph G)
{
    int v = G.V;
    onPath = vector<bool>(v, false);
    visited = vector<bool>(v, false);
    for (int i = 0; i < v; ++i)
    {
        traverse(G, i);
    }
    if (hasCycle)
    {
        return {};
    }
    reverse(postorder.begin(), postorder.end());
    return postorder;
}
void traverse(Graph G, int s)
{
    if (onPath[s])
    {
        hasCycle = true;
    }
    if (visited[s] || hasCycle)
    {
        return;
    }
    onPath[s] = true;
    visited[s] = true;
    for (auto& neighbor : G.adj[s])
    {
        traverse(G, neighbor);
    }
    postorder.push_back(s);
    visited[s] = false;
}
//无权最短路径:BFS遍历用step记录即可
int BFS(Graph G,int start,int target,int size)
{
    queue<int>q;
    vector<bool>visited(size);
    q.push(start);
    visited[start] = true;
    int step = 0;
    while (!q.empty())
    {
        int sz = q.size();
        for (int i = 0; i < sz; ++i)
        {
            int cur = q.front(); q.pop();
            if (cur == target)
            {
                return step;
            }
            for (auto neighbor : G.adj[cur])
            {
                if (!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        step++;
    }
    return -1;
}
//单源加权最短路径算法：Dijkstra算法
//本质BFS加贪心
vector<int>Dijkstra(WeightedGraph G,int start,int size)
{
    auto cmp = [](pair<int, int>& a, pair<int, int>& b)
        {
            return a.second > b.second;
        };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)>pq(cmp);
    pq.push({start,0});
    vector<int>res(size);
    res[start] = 0;
    while (!pq.empty())
    {
        int sz = pq.size();
        for (int i = 0; i < sz; ++i)
        {
            pair<int, int>cur = pq.top();
            pq.pop();
            int curnode = cur.first;
            int curvalue = cur.second;
            if (res[curnode] < curvalue)
            {
                continue;
            }
            for (auto neighbor : G.adj[curnode])
            {
                int nextnode = neighbor.first;
                int nextvalue = neighbor.second;
                if (curvalue+nextvalue<res[nextnode])
                {
                    res[nextnode] = curvalue + nextvalue;
                    pq.push({ nextnode,curvalue + nextvalue });
                }
            }
        }
    }
    return res;
}
