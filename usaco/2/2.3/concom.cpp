/*
ID: yuziyum1
LANG: C++
TASK: concom
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("concom.in");
    ofstream fout("concom.out");
    solve(fin,fout);
#endif
}

static int shares[101][101];
static bool controls[101][101];

void dfs(int i, int j){
    if(controls[i][j]){
        return;
    }
    controls[i][j] = true;
    for(int k = 1; k <= 100; ++k){
        // i 控股 j,把所有j控股的比例加到i->k上面
        shares[i][k] += shares[j][k];
        if(shares[i][k]>50){
            dfs(i,k);
        }
    }
}

void solve(istream &in,ostream &out){

    //start solve the problem
    int number;
    in >> number;
    int i, j, share;
    while(in >> i >> j >> share){
        shares[i][j] = share;
    }

    for(int i = 1; i <= 100; ++i){
        for(int j = 1; j <= 100; ++j){
            if(shares[i][j]>50){
                dfs(i,j);
            }
        }
    }

    for(int i = 1; i <= 100; ++i){
        for(int j = 1; j <= 100; ++j){
            if(i != j && controls[i][j] ){
                out << i << ' ' << j << endl;
            }
        }
    }

}

