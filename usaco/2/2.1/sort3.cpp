/*
ID: yuziyum1
LANG: C++
TASK: sort3
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
    ifstream fin("sort3.in");
    ofstream fout("sort3.out");
    solve(fin,fout);
#endif
}

int records[1000];
int recordNumber;
int counts[4];

//wrongPos[i][j]表示值为i，但在j的位置上的个数
int wrongPos[4][4];

void solve(istream &in,ostream &out){
    //start solve the problem
    
    in >> recordNumber;
    for(int i = 0; i < recordNumber; ++i){
        in >> records[i];
        counts[records[i]]++;
    }

    counts[0] = 0;
    counts[2] += counts[1];
    counts[3] += counts[2];

    int exchangeTimes = 0;
    for(int j = 1; j <=3; ++j){
        for(int i = counts[j-1]; i < counts[j]; ++i){
            wrongPos[j][records[i]]++;
        }
    }

    for(int i = 2; i <= 3; ++i){
        for(int j = 1; j < i; ++j){
            //直接交换
            int exchange = min(wrongPos[i][j],wrongPos[j][i]);
            exchangeTimes += exchange;
            wrongPos[i][j] -= exchange;
            wrongPos[j][i] -= exchange;
        }
    }
    
    exchangeTimes += min(min(wrongPos[1][2],wrongPos[2][3]),wrongPos[3][1])*2;
    exchangeTimes += min(min(wrongPos[1][3],wrongPos[3][2]),wrongPos[2][1])*2;

    out << exchangeTimes << endl;

}

