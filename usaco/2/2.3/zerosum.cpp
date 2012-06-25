/*
ID: yuziyum1
LANG: C++
TASK: zerosum
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
    ifstream fin("zerosum.in");
    ofstream fout("zerosum.out");
    solve(fin,fout);
#endif
}

int number;
char ops[9];
ostream *gOut;

bool isSolution() {
    int sum = 0;
    char lastOp = '+';
    int rightValue = 1;
    for(int i = 0; i <= number; ++i){
        if(i != number && ops[i] == ' '){
            rightValue = rightValue * 10 + (i+2);
        }else{
            if(lastOp == '+'){
                sum += rightValue;
            }else if(lastOp == '-'){
                sum -= rightValue;
            }
            rightValue = i+2;
            lastOp = ops[i];
        }
    }
    
    return sum == 0;
}

void dfs(int depth){

    if(depth == number - 1){
        if(isSolution()){
            *gOut << 1;
            for(int i = 0; i < depth; ++i){
                *gOut << ops[i] << i+2;
            }
            *gOut << endl;
        }
        return;
    }
    ops[depth] = ' ';
    dfs(depth+1);
    ops[depth] = '+';
    dfs(depth+1);
    ops[depth] = '-';
    dfs(depth+1);
}

void solve(istream &in,ostream &out){

    in >> number;
    gOut = &out;
    dfs(0);

}

