/*
ID: yuziyum1
LANG: C++
TASK: ariprog
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");
    solve(fin,fout);
#endif
}


void solve(istream &in,ostream &out){
    //start solve the problem
    
    
    int length;
    int upperBound;
    in >> length >> upperBound;

    
    static bool bitmap[250*250*2 + 1];
    memset(bitmap, 0, sizeof(bitmap) );
    for(int i = 0; i <= upperBound; ++i){
        for(int j = 0; j<= upperBound; ++j){
            bitmap[i*i+j*j] = true;
        }
    }


    int maxnum = upperBound*upperBound*2;
    int maxDiff = ceil(maxnum / (length-1));

    bool hasResult = false;

    /*O(maxDiff*maxStart*length)=O(maxnum^2)*/
    for(int diff = 1; diff <= maxDiff; ++diff){

        int maxStart = maxnum - diff*(length-1);
        for(int start = 0; start <= maxStart; ++start){

            if( !bitmap[start] ){
                continue;
            }

            int t = start;
            int n;
            for(n = 1; n < length; ++n){
                t+=diff;
                if(t>maxnum||!bitmap[t]){
                    break;
                }
            }

            if( n == length ){
                //found
                hasResult = true;
                out<<start<<' '<<diff<<endl;
            }

        }
    }

    if(!hasResult){
        out<<"NONE"<<endl;
    }

}

