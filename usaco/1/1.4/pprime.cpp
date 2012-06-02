/*
ID: yuziyum1
LANG: C++
TASK: pprime
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
    ifstream fin("pprime.in");
    ofstream fout("pprime.out");
    solve(fin,fout);
#endif
}

//素数表
int primes[10001];
int primeLen = 0;
//结果数组
int result[10000];
int resultLen = 0;
//起始范围
int scopeStart, scopeEnd;

void buildPrimeTable();
bool isPrime(int number);
void dfs(long long number,int len);

void solve(istream &in,ostream &out){
    //start solve the problem
    buildPrimeTable();
    in >> scopeStart >> scopeEnd;

    memset(result, 0, sizeof(result));

    for(int i = 0; i < 10; ++i){
        dfs(i, 1);
    }

    //数字为偶数个
    dfs(0,0);

    sort(&result[0], &result[resultLen]);
    for(int i = 0; i < resultLen; ++i){
        out << result[i] <<endl;
    }

}

void dfs(long long number,int len){

    if( number > scopeEnd || len > 9 ){
        return;
    }

    if( number >= scopeStart && isPrime(number) ){
        result[resultLen++] = number;
    }

    for(int i = 0; i < 10; ++i){
        //左右各加一个i
        dfs( (number+(long long)pow(10,len)*i)*10+i, len+2);
    }

}

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

