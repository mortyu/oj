/*
ID: yuziyum1
LANG: C++
TASK: $PROG
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(fin,fout);
#else
    ifstream fin("$PROG.in");
    ofstream fout("$PROG.out");
    solve(fin,fout);
#endif
}

void solve(istream &in,ostream &out){
    //start solve the problem
}

