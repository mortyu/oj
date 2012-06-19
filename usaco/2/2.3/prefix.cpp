/*
ID: yuziyum1
LANG: C++
TASK: prefix
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");
    solve(fin,fout);
#endif
}

vector< string> prefix;
char sequence[200001];
bool hasPrefix[200002];

void solve(istream &in,ostream &out){
    //start solve the problem
    string s;
    while( in >> s && s != "." ){
        prefix.push_back(s);
    }

    while( in >> s ){
        strcat(sequence, s.c_str() );
    }

    int i;

    hasPrefix[0] = true;
    int maxPrefixLen = 0;
    for(i = 0; sequence[i] != '\0'; ++i){

        for(vector<string>::iterator j = prefix.begin(); 
                j != prefix.end();
                ++j) {
            int k = 0;
            int len = j->size();
            int t = i + 1 - len;
            if( t < 0 ){
                continue;
            }
            if(!hasPrefix[t] ){
                continue;
            }
            for(k = 0; k < len ; ++k){
                if(sequence[t+k] !=(*j)[k]){
                    break;
                }
            }
            if(k == len){
                maxPrefixLen = i + 1;
                hasPrefix[maxPrefixLen] = true;
                break;
            }
        }
    }

    out << maxPrefixLen << endl;

}

