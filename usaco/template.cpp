/*
ID: yuziyum1
LANG: C++
TASK: $PROG
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
    ifstream fin("$PROG.in");
    ofstream fout("$PROG.out");
    solve(fin,fout);
#endif
}

void solve(istream &in,ostream &out){
    //start solve the problem
    
}

