/*
ID: yuziyum1
LANG: C++
TASK: numtri
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
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");
    solve(fin,fout);
#endif
}


void solve(istream &in,ostream &out){
    //start solve the problem

    int rowNum;
    in >> rowNum;

    static int dp[1001][1001];
    memset(dp, 0, sizeof(dp) );

    int result = 0;
    for(int i = 1; i <= rowNum; ++i){
        for(int j = 1; j <= i; ++j){
            in >> dp[i][j];
            dp[i][j] += max(dp[i-1][j-1], dp[i-1][j]);
            result = max(result, dp[i][j]);
        }
    }

    out << result << endl;

}

