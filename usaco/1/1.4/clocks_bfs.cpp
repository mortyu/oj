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
    //״̬ת�����Ե�n��ʱ�Ӳ�����bitpos = n * 2;
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
        //ת����18λ����������ÿ��λ��ʾһ��ʱ�ӵ�״̬
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
    //�������

    //��¼������һ״̬��֮ǰ����
    static int edges[1<<18];
    //��¼��һ״̬�ĸ�״̬
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

            //������9�ֲ���
            subStatus = doOperation(status, i);

            if( parent[subStatus] ){
                //֮ǰ��������
                continue;
            }

            //��¼������һ״̬��֮ǰ����
            edges[subStatus] = i + 1;
            //��¼��״̬
            parent[subStatus] = status;

            if( subStatus == 0 ){
                //�ҵ���,����Ҳ���·��
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

