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
int pastureNum; //�ڵ����
int locationsX[maxnum]; //���ڵ�x����
int locationsY[maxnum]; //���ڵ�y����
bool adjacenty[maxnum][maxnum]; //�ڵ�������ڽӾ���
double distances[maxnum][maxnum]; //distances[i][j] : �ڵ�i��j֮�����̾���
double maxdist[maxnum]; //maxdist[i] : �ڵ�i�������ɴ�ڵ����Զ����
int colors[maxnum];//�����ڵ���ɫ�����������ͨ��ͼ
double diameters[maxnum]; //diameters[colors[i]]��i�ڵ����ڵ���ͨ��ͼ��diameter
const double NOPATHDISTANCE = DBL_MAX / 2;

double getDistance(int x1, int y1, int x2, int y2){
    //��ȡ�������ֱ�߾���
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void floyd(){
    //floyd�㷨�������ڵ������·������
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
    //�ݹ���ڵ���ɫ������ͨ��ͼ
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
                //����ÿ���ڵ㵽������ͨ��ͼ�������ڵ�������
                maxdist[i] = max(maxdist[i], distances[i][j]);
            }
        }
        //����ڵ�i���ڵ���ͨ��ͼ��diameter
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
                //��ֱ��Ҫô����(i,j)�߶Σ�Ҫô������.
                //�������(i,j)�߶�,��ô��ֱ��=dist(i,j)+i���ܵ�����Զ����+j�ܵ�����Զ����
                //���������(i,j)�߶Σ���ô��ֱ��Ϊԭ����ͨ��ͼ�Ľϴ�ֵ
                double diameter = max(dist + maxdist[i] + maxdist[j], max(diameters[colors[i]], diameters[colors[j]]) );
                mindiameter = min(mindiameter, diameter);
            }
        }
    }

    out << setiosflags(ios::fixed) << setprecision(6) << mindiameter << endl;

}

