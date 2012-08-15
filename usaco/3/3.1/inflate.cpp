/*
ID: yuziyum1
LANG: C++
TASK: inflate
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
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");
    solve(fin,fout);
#endif
}

//数量不限的背包问题
void solve(istream &in,ostream &out){

    const int MAX_CONTEST_LEN = 10000;
    const int MAX_CATEGORY_NUM = 10000;

    static unsigned int dp[MAX_CONTEST_LEN+1];
    static unsigned int points[MAX_CATEGORY_NUM];
    static unsigned int minutes[MAX_CATEGORY_NUM];

    memset(dp, 0, sizeof(dp));

    int contest_length, category_num;
    in >> contest_length >> category_num;

    for(int i = 0; i < category_num; ++i) {
        in >> points[i] >> minutes[i];
        for(int minute = minutes[i]; minute <= contest_length; ++minute){
            dp[minute] = max(dp[minute], dp[minute-minutes[i]]+points[i]);
        }
    }

    out << dp[contest_length] << endl;
}

