#ifndef GRAPH_H
#define GRAPH_H
#include <algorithm>
#include<unordered_map>
#include <stdio.h>	// exit()函数需要用到的头文件
#include<vector>
#define X 9999	//相当于无穷大

class Graph
{
    private:
        static Graph* instance;		//创建实例：类是一个抽象类，实例可方便用于调取类成员的方法函数
        int n, m;	//n是顶点个数，m是边数
        char* data;		//顶点数组，用来储存顶点(char类型) idx ->char
        int** w;	//weight 边的权重，adjacencyMatrices
        int** path; //用来记录最小边权值顶点的序号，邻接矩阵
        std::unordered_map<char,int> ver_map; 
        std::vector<char> idx_vec;
        std::unordered_map<int,char> idx_map; 
    public:
        Graph();
        virtual ~Graph();		//虚析构函数，用来程序结束后释放new的内存
        static Graph* getInstance();	//获取实例

        void createGraph(Graph& G);
        int getIndex(const Graph& G, char v);	//获取顶点v的在顶点数组data中的下标
        void Floyd(Graph& G);
        void showPath(const Graph& G, int u, int v);	//展示最短路径

};
#endif // GRAPH_H
