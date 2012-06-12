/*
ID: yuziyum1
LANG: C++
TASK: subset
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
    ifstream fin("subset.in");
    ofstream fout("subset.out");
    solve(fin,fout);
#endif
}

//不用long long会溢出
long long sum[39*(39+1)/2+1];

void solve(istream &in,ostream &out){
    //start solve the problem

    int maxNumber;
    in >> maxNumber;

    if(maxNumber * (maxNumber+1) %4 !=0 ){
        out << 0 << endl;
        return;
    } 

    sum[0] = 1;
    for(int i = 1; i <= maxNumber; ++i) {
        int max = i*(i-1)/2;
        //从向后前，就不会重复计算了。只需要一维数组。
        for(int j = max; j >= 0; --j) {
            sum[i+j] += sum[j];
        }
    }

    out << sum[maxNumber*(maxNumber+1)/4]/2 << endl;

}

