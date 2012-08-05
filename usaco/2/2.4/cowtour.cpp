/*
ID: yuziyum1
LANG: C++
TASK: cowtour
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cfloat>
#include <cmath>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("cowtour.in");
    ofstream fout("cowtour.out");
    solve(fin,fout);
#endif
}

const int maxnum = 150;
int pastureNum; //节点个数
int locationsX[maxnum]; //各节点x坐标
int locationsY[maxnum]; //各节点y坐标
bool adjacenty[maxnum][maxnum]; //节点输入的邻接矩阵
double distances[maxnum][maxnum]; //distances[i][j] : 节点i和j之间的最短距离
double maxdist[maxnum]; //maxdist[i] : 节点i到其他可达节点的最远距离
int colors[maxnum];//给各节点着色，以区别各连通子图
double diameters[maxnum]; //diameters[colors[i]]：i节点所在的连通子图的diameter
const double NOPATHDISTANCE = DBL_MAX / 2;

double getDistance(int x1, int y1, int x2, int y2){
    //获取两坐标的直线距离
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void floyd(){
    //floyd算法求两两节点间的最短路径长度
    for(int k = 0; k < pastureNum; ++k){
        for(int i = 0; i < pastureNum; ++i){
            for(int j = 0; j < pastureNum; ++j){
                distances[j][i] = distances[i][j] = min(distances[i][j], distances[i][k]+distances[k][j]);
            }
        }
    }
}

void doColor(int index, int color_number){
    if(colors[index] != 0){
        return;
    }
    colors[index] = color_number;
    for(int i = 0; i < pastureNum; ++i){
        if(adjacenty[i][index]){
            doColor(i, color_number);
        }
    }
}

void color(){
    //递归给节点着色，求连通子图
    int color_number = 0;
    for(int i = 0; i < pastureNum; ++i){
        if(!colors[i]){
            doColor(i, ++color_number);
        }
    }
}

void computeMaxDist(){
    for(int i = 0; i < pastureNum; ++i) {
        maxdist[i] = 0;
        for(int j = 0; j < pastureNum; ++j){
            if(i != j && colors[i] == colors[j]){
                //计算每个节点到所在连通子图的其他节点的最长距离
                maxdist[i] = max(maxdist[i], distances[i][j]);
            }
        }
        //计算节点i所在的连通子图的diameter
        diameters[colors[i]] = max(diameters[colors[i]], maxdist[i]);
    }
}

void solve(istream &in,ostream &out){
    //start solve the problem

    in >> pastureNum;
    for(int i = 0; i < pastureNum; ++i) {
        in >> locationsX[i] >> locationsY[i];
    }

    char tmp;
    for(int i = 0; i < pastureNum; ++i){
        for(int j = 0; j < pastureNum; ++j) {
            in >> tmp;
            adjacenty[i][j] = tmp - '0';
            if(adjacenty[i][j]){
                distances[i][j] = distances[j][i] 
                    = getDistance(locationsX[i], locationsY[i], locationsX[j], locationsY[j]);
            }else{
                distances[i][j] = distances[j][i] = NOPATHDISTANCE;
            }
        }
    }

    floyd();
    color();
    computeMaxDist();

    double mindiameter = NOPATHDISTANCE;
    for(int i = 0; i < pastureNum; ++i){
        for(int j = 0; j < pastureNum; ++j) {
            if(colors[i] != colors[j]){
                double dist = getDistance(locationsX[i], locationsY[i], locationsX[j], locationsY[j]);
                //新直径要么经过(i,j)线段，要么不经过.
                //如果经过(i,j)线段,那么新直径=dist(i,j)+i所能到的最远距离+j能到的最远距离
                //如果不经过(i,j)线段，那么新直径为原两连通子图的较大值
                double diameter = max(dist + maxdist[i] + maxdist[j], max(diameters[colors[i]], diameters[colors[j]]) );
                mindiameter = min(mindiameter, diameter);
            }
        }
    }

    out << setiosflags(ios::fixed) << setprecision(6) << mindiameter << endl;

}

