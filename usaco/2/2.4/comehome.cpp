/*
ID: yuziyum1
LANG: C++
TASK: comehome
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("comehome.in");
    ofstream fout("comehome.out");
    solve(fin,fout);
#endif
}

int getNode(char a){
    if(a >= 'A' && a <='Z'){
        return 26 + a - 'A';
    }else if(a >= 'a' && a <= 'z'){
        return a - 'a';
    }
}

const int NOPATH = INT_MAX / 2;
int distances[52][52];

void floyd(){
    for(int k = 0; k < 52; ++k){
        for(int i = 0; i < 52; ++i){
            for(int j = 0; j < 52; ++j){
                distances[i][j] = min(distances[i][j], distances[i][k]+distances[k][j]);
            }
        }
    }
}

void solve(istream &in,ostream &out){
    //start solve the problem
    int number;
    in >> number;
    char node1, node2;
    int node1num, node2num;
    int dist;

    for(int i = 0; i < sizeof(distances)/sizeof(distances[0]); ++i){
        for(int j = 0; j < sizeof(distances[0])/sizeof(distances[0][0]); ++j){
            distances[i][j] = NOPATH;
        }
    }

    while(number--){
        in >> node1 >> node2 >> dist;
        node1num = getNode(node1);
        node2num = getNode(node2);
        //两点间可能有多条路径,取最短那条
        distances[node1num][node2num] 
            = distances[node2num][node1num] 
            = min(dist,distances[node1num][node2num]);
    }

    floyd();

    int shortest = INT_MAX;
    char result = 'A';
    for(int i = 26; i < 51; ++i){
        if(distances[i][51] < shortest){
            shortest = distances[i][51];
            result = 'A'+i-26;
        }
    }

    out << result <<' ' << shortest << endl;

}

