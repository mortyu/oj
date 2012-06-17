/*
ID: yuziyum1
LANG: C++
TASK: lamps
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
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");
    solve(fin,fout);
#endif
}

vector<bool> states;
vector<vector<bool> >results;
vector<int> finalOn, finalOff;
int opNumber;

void backtracing(int depth, int opCnt){

    if(opCnt>opNumber){
        return;
    }

    if(depth == 4){

        if( (opNumber-opCnt)%2 != 0){
            return;
        }

        for(int i = 0; i < finalOn.size(); ++i){
            if(!states[finalOn[i]]){
                return;
            }
        }
        for(int i = 0; i < finalOff.size(); ++i){
            if(states[finalOff[i]]){
                return;
            }
        }

        results.push_back( states );

        return;
    }

    backtracing(depth+1,opCnt);
    vector<bool> saved  = states;
    int size = states.size();

    if(depth == 0){
        for(int i = 1; i < size; ++i){
            states[i] = !states[i];
        }
    }else if(depth == 1){
        for(int i = 1; i < size; ++i){
            if(i&1){
                states[i] = !states[i];
            }
        }
    }else if(depth ==2 ){
        for(int i = 1; i < size; ++i){
            if(!(i&1)){
                states[i] = !states[i];
            }
        }
    }else if(depth == 3){
        for(int i = 1; i < size; ++i){
            if( (i-1)%3 == 0){
                states[i] = !states[i];
            }
        }
    }

    backtracing(depth+1,opCnt+1);
    states = saved;

}

bool cmp(const vector<bool> &a, const vector<bool> &b){
    int size = a.size();
    for(int i = 0; i < size; ++i){
        if(a[i]!=b[i]){
            return a[i] < b[i];
        }
    }
    return true;
}

void solve(istream &in,ostream &out){
    //start solve the problem

    int lampNumber;
    in >> lampNumber; 
    in >> opNumber;

    states = vector<bool>(lampNumber+1,true);

    finalOn.reserve(lampNumber+1);
    finalOff.reserve(lampNumber+1);

    int tmp;
    while(in>>tmp&&tmp!=-1){
        finalOn.push_back(tmp);
    }

    while(in>>tmp&&tmp!=-1){
        finalOff.push_back(tmp);
    }

    backtracing(0, 0);

    if(results.size() == 0){
        out << "IMPOSSIBLE" << endl;
        return;
    }

    sort(results.begin(), results.end(), cmp);
    for(int i = 0; i < results.size(); ++i){
        int size = results[i].size();
        for(int j = 1; j < size; ++j){
            out << results[i][j];
        }
        out << endl;
    }
}

