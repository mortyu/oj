/*
ID: yuziyum1
LANG: C++
TASK: agrinet
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");
    solve(fin,fout);
#endif
}

const int MAX_NODE_NUM = 100;
int node_number;
int matrix[MAX_NODE_NUM][MAX_NODE_NUM];
bool mark[MAX_NODE_NUM];

struct queue_node
{
    int cost;
    int vertex;

    queue_node(int c, int n):cost(c),vertex(n){
    }

    bool operator< (const queue_node &a) const{
        //生成小顶堆
        return cost > a.cost;
    }
};

struct edge{
    int cost;
    int vertexa, vertexb;
    bool operator < (const edge &a) const{
        return cost < a.cost;
    }
};

//prim算法，以节点为主
int prim_mst(){

    memset(mark, 0, sizeof(mark));
    priority_queue<queue_node> pq;

    int mst = 0;
    pq.push(queue_node(0, 0));
    while(!pq.empty()){
        queue_node node = pq.top();
        pq.pop();
        //已加入最小生成树，忽略
        if(mark[node.vertex]){
            continue;
        }
        //当前生成树之外的最外结点，加进来
        mark[node.vertex] = true;
        mst += node.cost;
        for(int i = 0; i < node_number; ++i){
            if(i != node.vertex && !mark[i]){
                pq.push(queue_node(matrix[node.vertex][i], i));
            }
        }
    }

    return mst;
}

void solve(istream &in,ostream &out){
    //start solve the problem

    memset(matrix, 0, sizeof(matrix));
    in >> node_number;
    for(int i = 0; i < node_number; ++i) {
        for(int j = 0; j < node_number; ++j) {
            in >> matrix[i][j];
        }
    }

    out << prim_mst() << endl;
}

