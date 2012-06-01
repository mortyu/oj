/*
ID: yuziyum1
LANG: C++
TASK: milk3
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
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");
    solve(fin,fout);
#endif
}

//记录某一状态是否访问过
bool bitmap[21][21][21];
//记录A空的时候，C的剩余量
bool cVisted[21];
//3个容量的容积
int capacities[3];
//当前剩余量
int current[3];

void dfs(int *left);

void solve(istream &in,ostream &out){
    //start solve the problem

    for(unsigned int i = 0; i < sizeof(capacities)/sizeof(capacities[0]); ++i){
        in >> capacities[i];
    }

    memset(bitmap,0,sizeof(bitmap));
    memset(cVisted,0,sizeof(cVisted));

    current[0] = current[1] = 0;
    current[2] = capacities[2];
    dfs(current);

    bool first = true;
    for(unsigned int i = 0; i < sizeof(cVisted)/sizeof(cVisted[0]); ++i){
        if( cVisted[i] ){
            if(first){
                out << i;
                first = false;
            }else{
                out << ' ' << i;
            }
        }
    }
    out << endl;

}

void dfs(int *left){

    bitmap[left[0]][left[1]][left[2]] = true;
    if( left[0] == 0 ){
        cVisted[left[2]] = true;
    }

    for(unsigned int i = 0; i < 3; ++i){
        for(unsigned int j = 0; j < 3; ++j){

            if(i == j){
                continue;
            }

            int copiedLeft[3];
            memcpy(copiedLeft,left,sizeof(copiedLeft));

            // i=>j
            int dump = min(capacities[j]-copiedLeft[j],copiedLeft[i]);
            copiedLeft[j]+=dump;
            copiedLeft[i]-=dump;

            if(!bitmap[copiedLeft[0]][copiedLeft[1]][copiedLeft[2]]) {
                dfs(copiedLeft);
            }

        }
    }

}

