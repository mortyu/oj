/*
ID: yuziyum1
LANG: C++
TASK: preface
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
    ifstream fin("preface.in");
    ofstream fout("preface.out");
    solve(fin,fout);
#endif
}

int value[] = {1,4,5,9,10,40,50,90,100,400,500,900,1000};
const char* symbol[] = {"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};

int cnt[26];

void getRomanNumber(int number){
    for(int i = sizeof(value)/sizeof(int) - 1 ; i >= 0 && number > 0 ; --i){
        while(number>=value[i]){
            number -= value[i];
            int n = strlen(symbol[i]);
            for(int j = 0; j < n; ++j){
                cnt[symbol[i][j]-'A']++;
            }
        }
    }
}

void solve(istream &in,ostream &out){
    int number;
    in >> number;
    for(int i = 1; i <= number; ++i){
        getRomanNumber(i);
    }
    char basicSymbols [] = {'I','V','X','L','C','D','M'};
    for(int i = 0; i < sizeof(basicSymbols)/sizeof(basicSymbols[0]); ++i){
        if(cnt[basicSymbols[i]-'A']!=0){
            out << basicSymbols[i] << ' ' << cnt[basicSymbols[i]-'A'] << endl;
        }
    }
}

