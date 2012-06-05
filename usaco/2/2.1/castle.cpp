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

    //Ϊ�˼򻯴��룬��1��ʼ�����账��߽�����
    for(int i = 1; i <= rows; ++i){
        for(int j = 1; j <= cols; ++j){
            if( colors[i][j] == 0){
                //��δȾɫ�ĸ���Ⱦ�µ�ɫ
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
        //��������
        for(int i = rows; i >= 1; --i){
            //��������

            int myColor = colors[i][j]; 
            int otherColor;

            for(int m = -1; m <= 1 ; ++m){
                //���ұ���ǽ
                for(int n = -1; n <= 1 ; ++n){
                    //���Ҷ���ǽ

                    if(m*m == n*n){
                        //������
                        continue;
                    }

                    // (-1,0),(1,0),(0,-1),(0,1)
                    otherColor = colors[i+m][j+n];

                    if( myColor == otherColor ){
                        continue;
                        //���ܻᵽΧǽ�⡣��Ϊǽ���colorCntΪ0������Ӱ���������账��߽�
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
    //���¸�����ɫ�ĸ�����
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

