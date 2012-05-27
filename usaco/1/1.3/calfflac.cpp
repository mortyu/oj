/*
ID: yuziyum1
LANG: C++
TASK: calfflac
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

void test();
void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    test();
    solve(cin,cout);
#else
    ifstream fin("calfflac.in");
    ofstream fout("calfflac.out");
    solve(fin,fout);
#endif
}

void solve(istream &in,ostream &out){
    //start solve the problem

    char buffer[20000];
    in.read(buffer,sizeof(buffer));

    int bufLen = strlen(buffer);

    int maxPalLen = 0;
    int resultLeft = 0;
    int resultRight = 0;

    for(int i = 0; i < bufLen; ++i) {

        if( !isalpha(buffer[i]) ){
            continue;
        }

        for(int j = 1; j >= 0; --j) {
            // j==1ʱ,���ĳ���Ϊ����
            // j==0ʱ,���ĳ���Ϊż��

            if( 2*(i+1)+j <= maxPalLen ){
                //��Ŀ��ܴ�Ҳ�ȵ�ǰ�������С��������������
                continue;
            }

            int left = i-j;
            int right = i+1;
            int len = j;

            while(true){

                while( left >=0 && !isalpha(buffer[left]) ){
                    left--;
                }

                while( right < bufLen && !isalpha(buffer[right]) ){
                    right++;
                }

                if( left>=0 && right < bufLen && 
                        toupper(buffer[left]) == toupper(buffer[right]) ){
                    len += 2;
                    if( len > maxPalLen ){
                        maxPalLen = len;
                        resultLeft = left;
                        resultRight = right;
                    }
                    left--;
                    right++;
                }else{
                    break;
                }
            }

        }
    }

    out << maxPalLen << endl;
    out.write(&buffer[resultLeft], resultRight-resultLeft+1);
    out<<endl;

}

void test(){
}
