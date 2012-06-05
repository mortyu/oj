/*
ID: yuziyum1
LANG: C++
TASK: frac1
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");
    solve(fin,fout);
#endif
}

int gcd(int m, int n);
int lcm(int m, int n);

struct fraction{

    int numerator;
    int denominator;

    fraction(int denominator,int numerator){
        int g = gcd(denominator,numerator);
        this->denominator = denominator/g;
        this->numerator = numerator/g;
    };

    bool operator< (const fraction &b) const{
        return  numerator * b.denominator - b.numerator*denominator < 0;
    }

    bool operator == (const fraction &b) const{
        return  b.numerator * denominator == numerator*b.denominator;
    }

    int gcd(int m, int n){

        if(m < n){
            return gcd(n, m);
        }
        if(n == 0){
            return m;
        }else{
            return gcd(n, m%n);
        }
    }

};

void solve(istream &in,ostream &out){
    //start solve the problem

    int n;
    in >> n;

    vector<fraction> v;

    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= i; ++j){
            v.push_back(fraction(i,j));
        } 
    }

    sort(v.begin(), v.end());
    vector<fraction>::iterator last  = unique(v.begin(), v.end());
    for(vector<fraction>::iterator i = v.begin();
            i != last;
            i++){
        out<<(i->numerator)<<'/'<<(i->denominator)<<endl;
    }

}

