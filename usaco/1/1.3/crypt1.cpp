/*
ID: yuziyum1
LANG: C++
TASK: crypt1
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
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");
    solve(fin,fout);
#endif
}


int digitSetSize;
int digits[10];
bool bitmap[10];
int multiplierA[3];
int multiplierB[2];

int dfs(int depth);
bool isValidResult();

void solve(istream &in,ostream &out){
    //start solve the problem

    in >> digitSetSize;

    memset(bitmap, 0 ,sizeof(bitmap));

    int i = 0;
    while(i < digitSetSize){
        in >> digits[i];
        bitmap[digits[i]] = true;
        i++;
    }

    out << dfs(0) << endl;

}

int dfs(int depth){
    //ö�����е����

    int cnt = 0;

    if( depth == 5 ){
        if( isValidResult() ){
            return 1;
        }
        return 0;
    }

    int *pointer = NULL;
    if( depth < 3 ){
        //ǰ�������浽����A��
        pointer = &multiplierA[depth];
    }else{
        //���������浽����B��
        pointer = &multiplierB[depth - 3];
    }

    for(int i = 0; i < digitSetSize; ++i) {
        *pointer = digits[i];
        cnt += dfs(depth + 1);
    }

    return cnt;

}

bool isValidResult(){
    //�Ƿ���Ч��

    int partial[2][10];
    memset(partial, 0 ,sizeof(partial));

    int carry = 0;
    int singleResult;

    for(int i = 0; i < 2; ++i ){
        carry = 0;
        for(int j = 0; j < 3; ++j ){
            singleResult = carry + multiplierB[i] * multiplierA[j];
            partial[i][j] = (singleResult) % 10;
            carry = singleResult / 10;
            if( !bitmap[ partial[i][j] ] ){
                //�Ƿ��ַ�����Ч��
                return false;
            }
        }
        if(carry != 0){
            //���һλ�н�λ����Ч��
            return false;
        }
    }
    
    carry = 0;
    for( int i = 1; i < 4; ++i){
        //�ۼ�������partial�����ڶ����������һλ�������
        singleResult = carry + partial[0][i]+partial[1][i-1];
        if( !bitmap[singleResult%10] ){
            return false;
        }
        carry = singleResult/10;
    }
    
    if(carry != 0){
        //�н�λ����Ч
        return false;
    }

    return true;
}

