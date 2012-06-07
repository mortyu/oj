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
int needs[1000];
int types;
int amounts[15][1000];

int solutionCnt = 0;

int getNumberOfOne(int number){
    int cnt = 0;
    while(number){
        number &= number-1;
        cnt++;
    }
    return cnt;
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

    int tmp[vitaminNumber];
    int max = (1 << types);
    int minNumber = INT_MAX;
    int solution = INT_MAX;
    for(int i = 1; i < max; ++i){
        memcpy(tmp, needs, sizeof(int)*vitaminNumber);
        for(int j = 0; j < types; ++j){
            if( (1 << j) & i ){
                for(int k = 0; k < vitaminNumber; ++k){
                    tmp[k] -= amounts[j][k];
                }
            }
        }

        int k;

        for(k = 0; k < vitaminNumber; ++k){
            if(tmp[k]>0){
                break;
            }
        }

        if( k == vitaminNumber ){
            int numberof1 = getNumberOfOne(i);
            if(numberof1 == minNumber){
                solution = min(solution, i);
            }else if(numberof1 < minNumber){
                minNumber = numberof1;
                solution = i;
            }
        }
    }

    out << minNumber;
    for(int j = 0; j < types; ++j){
        if( (1 << j) & solution){
            out << ' ' << (j+1);
        }
    }
    out << endl;

}

