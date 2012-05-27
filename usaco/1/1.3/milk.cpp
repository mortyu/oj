/*
ID: yuziyum1
LANG: C++
TASK: milk
*/


#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("milk.in");
    ofstream fout("milk.out");
    solve(fin,fout);
#endif
}

struct farmer{
    int price;
    int amount;

     // sort by the price
    bool operator< (const farmer& anotherFarmer) const{
        return price < anotherFarmer.price;
    };
};

void solve(istream &in,ostream &out){

    //greedy algorithm
    
    int milkNeeds, farmersNumber;
    in >> milkNeeds >> farmersNumber;
    
    farmer farmers[5000];
    int i = 0;
    while(i < farmersNumber) {
        in >> farmers[i].price >> farmers[i].amount;
        i++;
    }

    //sort by price. &farmers[farmersNumber] is the not included
    sort(&farmers[0],&farmers[farmersNumber]);

    int totalPrice = 0;
    int amount;
    for(i = 0; i < farmersNumber && milkNeeds > 0 ; ++i) {
        amount = min(milkNeeds,farmers[i].amount);
        milkNeeds -= amount;
        totalPrice += amount * farmers[i].price;
    }
    
    out << totalPrice << endl;

}

