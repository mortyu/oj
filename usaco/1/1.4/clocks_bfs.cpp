/*
ID: yuziyum1
LANG: C++
TASK: clocks
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;

void test();
void solve(istream &,ostream &);
stack<int> bfs(int status);

int main(){
#ifdef _DEV_
    test();
    solve(cin,cout);
#else
    ifstream fin("clocks.in");
    ofstream fout("clocks.out");
    solve(fin,fout);
#endif
}

int increase(int status,int bitpos){
    //状态转换。对第n个时钟操作，bitpos = n * 2;
    if( status & (1 << bitpos) ){
        status ^= (2<<bitpos);
    }
    status ^= ( 1 << bitpos);
    return status;
}

int doOperation(int status,int op){
    static const char* operations[] = 
    { "ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI" };
    int len = strlen(operations[op]);
    int pos;
    for(int i = 0; i < len; ++i){
        pos = (operations[op][i] - 'A') * 2;
        status = increase(status,pos);
    }
    return status;
}

void solve(istream &in,ostream &out){
    //start solve the problem

    int status = 0;
    int tmp;
    for(int i = 0; i < 9; ++i){
        //转换成18位二进制数。每两位表示一个时钟的状态
        in >> tmp;
        status |= ( (tmp/3%4) << (i*2) );
    }

    stack<int> s= bfs(status);
    bool first = true;
    while( !s.empty() ){
        if( first ){
            out << s.top();
            first = false;
        }else{
            out << ' '<<s.top();
        }
        s.pop();
    }
    out << endl;

}


stack<int> bfs(int start){
    //广度优先

    //记录到达这一状态的之前操作
    static int edges[1<<18];
    //记录这一状态的父状态
    static int parent[1<<18];

    memset(edges, 0, sizeof(edges));
    memset(parent, 0, sizeof(parent));

    queue<int> q;
    stack<int>result;
    parent[start] = -1;
    q.push(start);
    int status;
    while( !q.empty() ){

        status = q.front();
        q.pop();

        int subStatus;
        for(int i = 0; i < 9; ++i){

            //依次做9种操作
            subStatus = doOperation(status, i);

            if( parent[subStatus] ){
                //之前进过队列
                continue;
            }

            //记录到达这一状态的之前操作
            edges[subStatus] = i + 1;
            //记录父状态
            parent[subStatus] = status;

            if( subStatus == 0 ){
                //找到解,向后找操作路径
                while( subStatus != start ){
                    result.push(edges[subStatus]);
                    subStatus = parent[subStatus];
                }
                return result;
            }

            q.push( subStatus ) ;
        }
    }

    return result;
}

void test(){
    assert( increase(0x10,0) == 0x11);
    assert( increase(0x11,0) == 0x12);
    assert( increase(0x12,0) == 0x13);
    assert( increase(0x13,0) == 0x10);
    assert( increase(0x13,2) == 0x17);
}

