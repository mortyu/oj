/*
ID: yuziyum1
LANG: C++
TASK: sprime
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("sprime.in");
    ofstream fout("sprime.out");
    solve(fin,fout);
#endif
}

void buildPrimeTable();
bool isPrime(int number);
void dfs(int number, int depth, int maxdepth);

ostream *output;

void solve(istream &in,ostream &out){

    buildPrimeTable();

    int N;
    in >> N;

    output = &out;

    dfs(0,0,N);
    
}

void dfs(int number,int depth,int maxdepth){

    if( depth == maxdepth ){
        *output << number << endl;
        return;
    }

    for(int i = 1; i < 10; i+=1){
        int t = number * 10 + i;
        if( isPrime(t) ){
            dfs(t, depth+1, maxdepth);
        }
    }
}

//素数表
int primes[10001];
int primeLen = 0;

bool isPrime(int number){
    if( number < 2 ){
        return false;
    }
    int max = floor( sqrt(number) );
    for(int i = 0; i < primeLen && primes[i] <= max; ++i){
        if( number % primes[i] == 0 ){
            return false;
        }
    }
    return true;
}

/**
 * 筛数法算素数表
 *  
 */
void buildPrimeTable(){

    static bool notPrimeBitmap[10001];
    memset(notPrimeBitmap, 0, sizeof(notPrimeBitmap));

    notPrimeBitmap[2] = false;

    for(int i = 2; i*i < 10000; ++i){

        if( notPrimeBitmap[i] ){
            continue;
        }

        int maxMultiplier = 10000 / i;
        for(int j = 2; j <= maxMultiplier; ++j){
            notPrimeBitmap[i * j] = true;
        }

    }

    for(int i = 2; i < 10000; ++i){
        if( !notPrimeBitmap[i] ){
            primes[primeLen++] = i;
        }
    }

}

