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
    //compute �������Ľ����Ϊnumber,�߶�Ϊdepth��pedigree��̬��

    if(dp[number][depth]!=NOT_VISITED){
        return dp[number][depth];
    }

    if(number%2!=1 || depth <= 0 || number < depth){
        dp[number][depth] = 0;
        return 0;
    }

    if(number == 1){
        //ֻ��һ���ڵ�ʱ����̬����Ϊ1
        dp[number][depth] = 1;
        return 1;
    }

    int result = 0;
    for(int leftNumber = 1; leftNumber < number - 1; leftNumber += 2){
        //�������ڵ�����1��number-2���������Ϊż����㲻���γ�pedigree,����ÿ��+2

        for(int leftDepth = 1; leftDepth < depth-1; ++leftDepth){
            //�������ĸ߶�Ϊ1~(depth-2),�������߶�Ϊdepth-1
            result += compute(leftNumber, leftDepth) * compute(number - 1 - leftNumber, depth - 1);
            result %= 9901;
        }

        for(int rightDepth = 1; rightDepth < depth-1; ++rightDepth){
            //�������ĸ߶�Ϊdepth-1,�������߶�Ϊ(1~depth-2)�����
            result += compute(leftNumber, depth-1) * compute(number - 1 - leftNumber, rightDepth);
            result %= 9901;
        }

        //����������Ϊdepth-1�����
        result += compute(leftNumber,depth-1) * compute(number-1-leftNumber,depth-1);
        result %= 9901;
    }


    dp[number][depth] = result;
    return result;

}

void solve(istream &in,ostream &out){

    for(int i = 0; i < sizeof(dp)/sizeof(dp[0]); ++i){
        for(int j = 0; j < sizeof(dp[0])/sizeof(dp[0][0]); ++j){
            dp[i][j] = NOT_VISITED;
        }
    }

    int number, depth;
    in >> number >> depth;

    out << compute(number, depth) << endl;

}

