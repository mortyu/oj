/*
ID: yuziyum1
LANG: C++
TASK: nocows
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
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");
    solve(fin,fout);
#endif
}

const int NOT_VISITED = -1;
int dp[200][100];

int compute(int number, int depth){
    //compute �������Ľ����Ϊnumber,�߶�<=depth��pedigree��̬��

    if(dp[number][depth]!=NOT_VISITED){
        return dp[number][depth];
    }

    if(number%2!=1 || depth <= 0){
        dp[number][depth] = 0;
        return 0;
    }

    int result = 0;
    for(int leftNumber = 1; leftNumber < (number - 1)/2; leftNumber += 2){
        //�������ڵ�����1��number-2���������Ϊż����㲻���γ�pedigree,����ÿ��+2
        result += compute(leftNumber,depth-1) * compute(number-1-leftNumber,depth-1);
        result %= 9901;
    }

    result *= 2;
    result += compute((number-1)/2, depth-1)  *  compute((number-1)/2,depth-1);
    result %= 9901;

    dp[number][depth] = result;
    return result;

}

void solve(istream &in,ostream &out){

    dp[1][1] = 1;
    for(int i = 0; i < sizeof(dp)/sizeof(dp[0]); ++i){
        for(int j = 0; j < sizeof(dp[0])/sizeof(dp[0][0]); ++j){
            dp[i][j] = NOT_VISITED;
        }
    }

    int number, depth;
    in >> number >> depth;

    out << (9901 + compute(number, depth) - compute(number, depth-1) ) % 9901 << endl;

}

