/*
ID: yuziyum1
LANG: C++
TASK: checker
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
    ifstream fin("checker.in");
    ofstream fout("checker.out");
    solve(fin,fout);
#endif
}

int size;
int solutionsNumber = 0;
bool checkBoard[13][13];
int solution[13];
ostream *output;

void dfs(int depth);

void solve(istream &in,ostream &out){
    //start solve the problem
    
    output = &out;

    in >> size;

    memset(checkBoard, 0, sizeof(checkBoard) );
    dfs(0);
    *output << solutionsNumber << endl;

}

void outputSolution(){
    bool first = true;
    for(int i = 0; i < size; ++i){
        if( first ){
            *output << solution[i];
            first = false;
        }else{
            *output << ' ' << solution[i];
        }
    }
    *output << endl;
}

void dfs(int depth){

    if( depth == size ){
        solutionsNumber++;
        if( solutionsNumber <= 3 ){
            outputSolution();
        }
        return;
    }

    char saved[sizeof(checkBoard)];
    memcpy(saved, checkBoard, sizeof(checkBoard));

    for(int i = 0; i < size; ++i){

        if( checkBoard[depth][i] ){
            //不可放棋子
            continue;
        }

        memcpy(checkBoard, saved, sizeof(checkBoard));

        for(int j = depth+1; j < size; ++j){

            checkBoard[j][i] = true;

            if( i + (j - depth) < size){
                //右下角对角线位置
                checkBoard[j][i + (j - depth)] = true;
            }

            if( i - (j - depth) >= 0 ){
                //左下角对角线位置
                checkBoard[j][i - (j - depth)] = true;
            }

        }

        solution[depth] = i+1;
        checkBoard[depth][i] = true;

        dfs(depth+1);

    }

}

