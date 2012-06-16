/*
ID: yuziyum1
LANG: C++
TASK: runround
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("runround.in");
    ofstream fout("runround.out");
    solve(fin,fout);
#endif
}

int inputNumber = 0;

char str[11];

bool isrunRound(int number){

    static bool digitMask[10];

    int len = 0;
    while(number){
        str[len++] = number % 10;
        number /= 10;
    }

    memset(digitMask, 0, sizeof(digitMask));
    int left = len;
    int current = len - 1;

    while(left){

        if(digitMask[str[current]]){
            return false;
        }

        digitMask[str[current]] = true;
        current = (current + len - (str[current]%len) ) % len;
        left--;

    }

    return current == len - 1;

}

int permutation(int number, int left) {

    static int usedMask[10];

    if(left==0 && number>inputNumber && isrunRound(number)){
        return number;
    }

    int result;

    for(int i = 1; i < 10; ++i){
        if(!usedMask[i]){
            usedMask[i] = true;
            result = permutation(number*10+i,left-1);
            if(result != -1){
                return result;
            }
            usedMask[i] = false;
        }
    }

    return -1;

}

void solve(istream &in,ostream &out){


    //start solve the problem
    in >> inputNumber;
    int result;
    for(int i = floor(log10(inputNumber)); i <= 10; ++i){
        result = permutation(0, i);
        if(result!=-1){
            out << result << endl;
            return;
        }
    }

}

