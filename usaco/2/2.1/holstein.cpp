/*
ID: yuziyum1
LANG: C++
TASK: holstein
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("holstein.in");
    ofstream fout("holstein.out");
    solve(fin,fout);
#endif
}

int vitaminNumber;
int needs[25];
int types;

int amounts[15][25];
int path[15];
int solution[15];

int minNumber = INT_MAX;

void backtrace(int depth, int cnt) {

    if(depth > types) {
        return;
    }

    int i;
    for(i = 0; i < vitaminNumber; ++i) {
        if(needs[i] > 0) {
            break;
        }
    }

    if(i == vitaminNumber) {
        if(cnt < minNumber){
            minNumber = cnt;
            memcpy(solution, path, sizeof(solution));
        }
        //不需要其他feeds，不需要继续回溯
        return;
    }


    int saved[vitaminNumber];
    memcpy(saved, needs, sizeof(int)*vitaminNumber);
    for(i = 0; i < vitaminNumber; ++i) {
        needs[i] -= amounts[depth][i];
    }
    path[cnt] = depth;
    backtrace(depth+1, cnt+1);
    memcpy(needs, saved, sizeof(int)*vitaminNumber);
    backtrace(depth+1, cnt);

}

void solve(istream &in,ostream &out){
    //start solve the problem
    in >> vitaminNumber;
    for(int i = 0; i < vitaminNumber; ++i){
        in >> needs[i];
    }

    in >> types;
    for(int i = 0; i < types; ++i) {
        for(int j = 0; j < vitaminNumber; ++j) {
            in >> amounts[i][j];
        }
    }

    backtrace(0, 0);
    out << minNumber;
    for(int i = 0; i < minNumber; ++i) {
        out << ' ' << (solution[i] + 1);
    }
    out << endl;

}

