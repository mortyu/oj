/*
ID: yuziyum1
LANG: C++
TASK: money
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
    ifstream fin("money.in");
    ofstream fout("money.out");
    solve(fin,fout);
#endif
}

void solve(istream &in,ostream &out){
    //start solve the problem

    static long long dp[10001];

    int coins[26];
    int coinNumber, amount;
    in >> coinNumber >> amount;

    int i = 0;
    while( in >> coins[i] ){
        i++;
    }

    dp[0] = 1;
    for(int i = 0; i < coinNumber; ++i){
        for(int j = 1; j <= amount; ++j){
            dp[i][j] += dp[i-1][j];
        }
    }

    out << dp[amount] << endl;

}

