#include "Graph.h"
#include <iostream>
#include <fstream>
#include<vector>
#include<map>
#include <boost/dll/runtime_symbol_info.hpp>

using namespace std;

void splitString(string srcStr, vector<string>& v_splitStr,
                           string splitSymbol) {
    // 清空容器
    vector<string>().swap(v_splitStr);
    while (string::npos != srcStr.find_first_of(splitSymbol)) {
        // 获取第一个分隔符之前的文件类型
        string strT = srcStr.substr(0, srcStr.find_first_of(splitSymbol));
        // 将分割的字符加入到容器列表最后
        v_splitStr.push_back(strT);
        // 删除分割字符前面的，保留后面的字符串
        srcStr =
            srcStr.substr(srcStr.find_first_of(splitSymbol) + 1, srcStr.size());
    }
    // 最后的一个分割符号后面或者没有匹配到分割符号的字符加入容器列表
    v_splitStr.push_back(srcStr);
}


Graph::Graph()		//默认构造
{
    //ctor
}

Graph* Graph::instance = nullptr;	//固定套路
Graph* Graph::getInstance()		//同上，记住就好，也可以自己尝试理解下
{
    if(!instance) instance = new Graph();
    return instance;
}

int Graph::getIndex(const Graph& G, char v)		//获取顶点v在顶点数组中的下标
{
    for(int i = 0; i < G.n; i++)
        if(G.data[i] == v) return i;
    return -1;	//没找到就返回-1
}

void Graph::createGraph(Graph& G)
{
    cout << "please input the number of vertex and arc:";
    G.n=4;
    G.m=9;
    // cin >> G.n >> G.m;
    G.data = new char[G.n];		//动态创建一维数组
    cout << "please input the value of vertice:";
    char a[4]={'A','B','C','D'}; 
    idx_vec.resize(G.n);
    for(int p = 0; p < G.n; p++){
        // cin >> G.data[p];
        G.data[p]=a[p];
        ver_map[a[p]]=p;
        idx_vec[p]=a[p];
    }
        
    char v1, v2;
    int power, i, j;
    G.w = new int*[G.n];	//动态创建二维数组，申请了 int* 类型的G.n行空间
    for(int s = 0; s < G.n; s++)
        G.w[s] = new int[G.n];		//每一行申请一个int类型的G.n列空间

    for(int x = 0; x < G.n; x++)
        for(int y = 0; y < G.n; y++){
            if(x == y) G.w[x][y] = 0;	//边的邻接矩阵中左对角线权重（即自己的权重）都设为0，因为是多源的
            else G.w[x][y] = X;		//其他边的权重初始化为无穷大
        }

    cout << "please input the weight of arc between 2 vertice as 100 A B:\n" << endl;
    std::string lintxt;
    std::ifstream infile;
    infile.open("/home/d/githubPro/casadi_test/src/cc_test/build/topograph.txt");
    if(!infile.is_open()){
        std::cout<<"can not open file \n"<<std::endl;
        return ;
    }
    std::vector<string> vex;
    while(getline(infile,lintxt)){
        vex.emplace_back(lintxt);
    }
    
    for(int k = 0; k < G.m; k++){
        std::vector<string> lineStr;
        std::string splitSymbol{' '};
        splitString(vex[k],lineStr,splitSymbol);
        power=atoi(lineStr[0].c_str());
        string str0=lineStr[1];
        v1=*lineStr[1].c_str();
        string STR=lineStr[2];
        v2=*lineStr[2].c_str();
        // v2=*(vex[k].substr(vex[k].find(' ',2)+1,vex[k].back()).c_str());

        // cin >> power >> v1 >> v2;
        // i = getIndex(G, v1);
        // j = getIndex(G, v2);
        i=ver_map[v1];
        j=ver_map[v2];
        if(i == -1 || j == -1){	//没在顶点数组中找到对应的顶点下标
                cout << "Sorry, I can't find the vertex" << endl;
                exit(-1);	//直接退出程序
        }
        G.w[i][j] = power;	//有向图赋值边的权重
    }
}

void Graph::Floyd(Graph& G)
{
    G.path = new int*[G.n];		//动态创建二维数组
    for(int s = 0; s < G.n; s++){
        G.path[s] = new int[G.n];
        for(int t = 0; t < G.n; t++)
            G.path[s][t] = -1;	//初始化path邻接矩阵的值
    }
    //特别注意：不能用fill函数来初始化动态二维数组，因为动态new出来的空间不一定连续


    for(int v = 0; v < G.n; ++v)    //v是指在某两个点中，它们之间点的下标
        for(int i = 0; i < G.n; ++i)
            for(int j = 0; j < G.n; ++j)
                if(G.w[i][j] > G.w[i][v] + G.w[v][j])	
                {
                    G.w[i][j] = G.w[i][v] + G.w[v][j];
                    G.path[i][j] = v;
                }
}
std::vector<char> pathID;
void Graph::showPath(const Graph& G, int u, int v)
{	//看配合B站视频讲解效果更棒，该函数不多做解释！

    if(G.path[u][v] == -1) 
    {
        pathID.emplace_back(idx_vec[u]);
        cout << G.data[u] << " to " << G.data[v] << endl;	//B站输出的是顶点序号，我这输出的是顶点的值
    }
    else{
        int mid = G.path[u][v];
        showPath(G, u, mid);
        showPath(G, mid, v);
    }
}

Graph::~Graph()		//虚析构函数作用：一般都是用来程序结束后释放new出来的内存
{
    delete[] data;

    for(int i = 0; i < n; i++)
        delete[] w[i];
    delete[] w;

    for(int i = 0; i < n; i++)
        delete[] path[i];
    delete[] path;
}

using namespace std;
struct inner{
    int x=0;
};
void test_inner(){
    inner* mInner;
    int& mx=mInner->x;
    mx=3;
    std::cout<<mInner->x<<" v \n";
}
int main()
{
    //TODO test_inner();
    char id='A';
    map<int,int> k;
    cout<<id<<endl;
    char v1, v2;
    int a, b;
    Graph G;
    Graph::getInstance()->createGraph(G);	//用实例来调取抽象类的函数方法
    Graph::getInstance()->Floyd(G);
    cout << "please input which two vertices you want to show the shortest path between them:";
    cin >> v1 >> v2;
    a = Graph::getInstance()->getIndex(G, v1);
    b = Graph::getInstance()->getIndex(G, v2);
    Graph::getInstance()->showPath(G, a, b);
    for(auto p:pathID){
        std::cout<<"path "<<p<<"->";
    }
    std::cout<<std::endl;
    return 0;
}
