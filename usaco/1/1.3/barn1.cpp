/*
ID: yuziyum1
LANG: C++
TASK: barn1
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
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");
    solve(fin,fout);
#endif
}

void solve(istream &in,ostream &out){
    
    int maxBoards, totalStalls, occupiedNumber;
    in >> maxBoards >> totalStalls >> occupiedNumber;

    int stalls[200], holes[200];
    int i;
    for(i = 0; i < occupiedNumber; ++i) {
        in >> stalls[i];
    }
    
    // sort the stall number in prevent of disordered input
    sort(&stalls[0], &stalls[occupiedNumber]);
    for(i = 0; i + 1 < occupiedNumber; ++i) {
        holes[i] = stalls[i + 1] - stalls[i] -1;
    }
    // sort the holes by the length from larger to smaller
    sort(&holes[0], &holes[occupiedNumber - 1], greater<int>() );

    // one board cover from the first to last
    int minBlocked = stalls[occupiedNumber - 1] - stalls[0] + 1;
    /* if multiply boards available, cut the holes from larger to smaller 
     * to reduce the number of stalls should be covered
     */
    int holesNumber = min(occupiedNumber - 1, maxBoards - 1); 
    for(i = 0; i < holesNumber ; ++i){
        minBlocked -= holes[i];
    }

    out << minBlocked << endl;

}

