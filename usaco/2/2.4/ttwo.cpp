/*
ID: yuziyum1
LANG: C++
TASK: ttwo
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");
    solve(fin,fout);
#endif
}

char map[12][12];
bool visited[12*12][12*12][4][4];

void solve(istream &in,ostream &out){
    //start solve the problem
    
    int farmerX, farmerY, farmerDir, cowX, cowY, cowDir;
    for(int i = 0; i < 12;  ++i){
        //栏上围墙，避免检测边界条件
        map[0][i] = '*';
        map[11][i] = '*';
        map[i][0] = '*';
        map[i][11] = '*';
    }

    string row;
    for(int i = 1; i < 11; ++i){
        in >> row;
        for(int j = 1; j < 11; ++j) {
            map[i][j] = row[j-1];
            if(map[i][j] == 'F'){
                farmerX = i;
                farmerY = j;
                farmerDir = 0;
            }else if(map[i][j] == 'C'){
                cowX = i;
                cowY = j;
                cowDir = 0;
            }
        }
    }

    //N, E, S, W每个方向对应的(x,y)的增量 
    int step[4][2] = {
        {-1,0},{0,1},{1,0},{0,-1}
    };

    int minutes = 0;
    do{

        //作标记以防无限循环
        visited[farmerX*12+farmerY][cowX*12+cowY][farmerDir][cowDir] = true;

        int nextX = farmerX+step[farmerDir][0];
        int nextY = farmerY+step[farmerDir][1];
        if(map[nextX][nextY]!='*'){
            farmerX = nextX;
            farmerY = nextY;
        }else{
            farmerDir = (farmerDir+1)%4; 
        } 

        nextX = cowX+step[cowDir][0];
        nextY = cowY+step[cowDir][1];
        if(map[nextX][nextY]!='*'){
            cowX = nextX;
            cowY = nextY;
        }else{
            cowDir = (cowDir+1)%4;
        }

        minutes++;
        if( farmerX == cowX && farmerY == cowY){
            //遇见
            break;
        }else if(visited[farmerX*12+farmerY][cowX*12+cowY][farmerDir][cowDir]){
            //已到过此状态，不可能再相遇了
            minutes = 0;
            break;
        }

    }while(true);

    out << minutes << endl;
}

