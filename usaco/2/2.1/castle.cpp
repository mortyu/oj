/*
ID: yuziyum1
LANG: C++
TASK: castle
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
    ifstream fin("castle.in");
    ofstream fout("castle.out");
    solve(fin,fout);
#endif
}

int rows, cols;
int breakWallRow, breakWallCol;
char breakWallOrient;
int newMaxRoomNumber;

int modules[52][52];
int colors[52][52];
int colorCnt[52*52];

void floodfill(int row, int col, int color);
void computeBreakWall();

void solve(istream &in,ostream &out){
    //start solve the problem

    in >> cols >> rows;

    for(int i = 1; i <= rows; ++i){
        for(int j = 1; j <= cols; ++j){
            in >> modules[i][j];
        }
    } 

    memset(colors, 0, sizeof(colors));
    memset(colorCnt, 0, sizeof(colorCnt));

    int color = 0;
    int maxRoomNumber = 0;

    //为了简化代码，从1开始，无需处理边界问题
    for(int i = 1; i <= rows; ++i){
        for(int j = 1; j <= cols; ++j){
            if( colors[i][j] == 0){
                //对未染色的格子染新的色
                floodfill(i, j, ++color);
                maxRoomNumber = max(maxRoomNumber, colorCnt[color]);
            }
        }
    } 


    out << color << endl;
    out << maxRoomNumber << endl;
    computeBreakWall();
    out << newMaxRoomNumber << endl;
    out << breakWallRow << ' ' << breakWallCol << ' ' << breakWallOrient << endl;
}

void computeBreakWall(){

    for(int j = 1; j <=cols; ++j){
        //从西向东找
        for(int i = rows; i >= 1; --i){
            //从南向北找

            int myColor = colors[i][j]; 
            int otherColor;

            for(int m = -1; m <= 1 ; ++m){
                //先找北边墙
                for(int n = -1; n <= 1 ; ++n){
                    //再找东边墙

                    if(m*m == n*n){
                        //非相邻
                        continue;
                    }

                    // (-1,0),(1,0),(0,-1),(0,1)
                    otherColor = colors[i+m][j+n];

                    if( myColor == otherColor ){
                        continue;
                        //可能会到围墙外。因为墙外的colorCnt为0，不会影响结果。无需处理边界
                    }

                    if( colorCnt[myColor] + colorCnt[otherColor] <= newMaxRoomNumber){
                        continue;
                    }

                    newMaxRoomNumber = colorCnt[myColor] + colorCnt[otherColor];
                    breakWallRow = i;
                    breakWallCol = j;

                    if( m == -1){
                        breakWallOrient = 'N';
                    }else{
                        breakWallOrient = 'E';
                    }

                }
            }
        }
    }
}

void floodfill(int row, int col, int color){

    if( colors[row][col] != 0){
        return;
    }

    colors[row][col] = color;
    //记下各种颜色的格子数
    colorCnt[color]++;

    if( !(modules[row][col] & 1) ){
        floodfill(row, col - 1, color);
    }

    if( !(modules[row][col] & 2) ){
        floodfill(row - 1, col, color);
    }

    if( !(modules[row][col] & 4) ){
        floodfill(row, col + 1, color);
    }

    if( !(modules[row][col] & 8) ){
        floodfill(row + 1, col, color);
    }

}

