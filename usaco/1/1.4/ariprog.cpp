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
    static int biSquareSet[sizeof(bitmap)/sizeof(bitmap[0])];
    memset(bitmap, 0, sizeof(bitmap) );
    for(int i = 0; i <= upperBound; ++i){
        for(int j = 0; j<= upperBound; ++j){
            bitmap[i*i+j*j] = true;
        }
    }

    int setLen = 0;
    for(int i = 0, len = upperBound*upperBound*2;
            i < len; ++i){
        if(bitmap[i]){
            biSquareSet[setLen++] = i;
        }
    }

    int maxnum = upperBound*upperBound*2;
    int maxDistance = ceil(maxnum / (length-1));

    bool hasResult = false;

    /*O(maxDistance*maxStart*length)=O(maxnum^2)*/
    for(int distance = 1; distance <= maxDistance; ++distance){

        int maxStart = maxnum - distance*(length-1);
        for(int i = 0; i < setLen && biSquareSet[i] <=maxStart ; ++i){

            int t = biSquareSet[i];
            int n;
            for(n = 1; n < length; ++n){
                t+=distance;
                if(t>maxnum||!bitmap[t]){
                    break;
                }
            }

            if( n == length ){
                //found
                hasResult = true;
                out << biSquareSet[i] << ' ' << distance <<endl;
            }

        }
    }

    if(!hasResult){
        out<<"NONE"<<endl;
    }

}

