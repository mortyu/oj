/*
ID: yuziyum1
LANG: C++
TASK: hamming
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
    ifstream fin("hamming.in");
    ofstream fout("hamming.out");
    solve(fin,fout);
#endif
}

/*
 *
 *
 * 00000000
 * 00000111
 * 00011001
 * 00011110
 *
 * 00000000 
 * 00000011
 * 00000011
*/

int countNumberOf1(int num){
    int result = 0;
    while(num){
        num &= num - 1;
        result++;
    }
    return result;
}

int getHammingDistance(int a, int b){
    return countNumberOf1(a^b);
}

void solve(istream &in,ostream &out){
    //start solve the problem
    int codeWordsLength, bitLength, hammingDistance;
    in >> codeWordsLength >> bitLength >> hammingDistance;

    int max = (1 << bitLength);
    int codeWords[64];
    int length = 0;
    codeWords[length++] = 0;
    for(int i = 1; i < max & length < codeWordsLength; ++i) {
        int j;
        for(j = 0; j < length; ++j){
            if(getHammingDistance(codeWords[j], i) < hammingDistance) {
                break;
            }
        }
        if(j == length){
            codeWords[length++] = i;
        }
    }

    for(int i = 0; i < length; ++i){ 
        if(i % 10 == 0){
            if(i != 0){
                out << endl;
            }
        }else{
            out << ' ';
        }
        out << codeWords[i];
    }
    out << endl;
}

