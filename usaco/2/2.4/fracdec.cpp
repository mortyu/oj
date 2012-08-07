/*
ID: yuziyum1
LANG: C++
TASK: fracdec
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");
    solve(fin,fout);
#endif
}

void solve(istream &in,ostream &out){
    //start solve the problem
    //

    static int visited[100001];
    static int frac[100001];
    int numerator, denominator;

    in >> numerator >> denominator;
    memset(visited, 0, sizeof(visited));

    int int_part = numerator/denominator;
    numerator = numerator % denominator;

    int cnt = 1;
    int cycle_start = 0;
    do{
        if(visited[numerator]){
            //Ñ­»·³öÏÖ
            cycle_start = visited[numerator];
            break;
        }
        visited[numerator] = cnt;
        numerator *= 10;
        frac[cnt++] = numerator/denominator;
        numerator = numerator % denominator;
    }while(numerator != 0);

    stringstream outputbuf;
    outputbuf << int_part << '.';
    for(int i = 1; i < cnt; ++i){
        if(i == cycle_start){
            outputbuf << '(';
        }
        outputbuf << frac[i];
    }

    if(cycle_start){
        outputbuf << ')';
    }

    outputbuf << endl;

    string result = outputbuf.str();
    for(int i = 0, n = result.size(); i < n; ++i){
        if(i && i % 76 == 0){
            out << endl;
        }
        out << result[i];
    }

}

