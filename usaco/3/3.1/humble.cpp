/*
ID: yuziyum1
LANG: C++
TASK: humble
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("humble.in");
    ofstream fout("humble.out");
    solve(fin,fout);
#endif
}

const int MAX_SET_SIZE = 100;
const int MAX_HUMBLE_NUMBER = 100000;
int prime_set[MAX_SET_SIZE];
long long humble_numbers[MAX_HUMBLE_NUMBER+1];

struct queue_node{
    int factor;
    long long humble_number;
    int index;
    bool operator> (const queue_node a) const{
        return humble_number > a.humble_number;
    }
};

/*
 *
 用小顶堆存储每个质数所能生成最小humble_number.依次弹出的堆顶，并补充被弹出的结点，这样就能得到我们所要的解。
 这里用优先队列来实现小顶堆.堆结点的数据结构为queue_none.
 struct queue_node{
    int factor; //对应相应的素数
    long long humble_number; //能被factor整除，且未加入humble_numbers的最小素数
    int index;// humble_number/factor所得到的humble_number所在humble_numbers数组中的index  这样当这个节点被弹出后，下一个humble_number值就是humble_numbers[index+1]*factor,无须再顺序查找
   };
    整个算法时间复杂度为O(N*log(k))
 * */
void solve(istream &in,ostream &out){

    int set_size;
    int n; 
    in >> set_size >> n;

    priority_queue<queue_node, vector<queue_node>, greater<queue_node> > q;
    queue_node node;
    for(int i = 0; i < set_size; ++i) {
        in >> prime_set[i];
        node.humble_number = node.factor = prime_set[i];
        node.index = 0;
        q.push(node);
    }

    humble_numbers[0] = 1;
    int humble_numbers_size = 1;
    int current_max_number = 1;

    while(humble_numbers_size <= n && !q.empty()){
        node = q.top();
        q.pop();
        if(node.humble_number > current_max_number){
            humble_numbers[humble_numbers_size++] = node.humble_number;
            current_max_number = node.humble_number;
        }
        node.index = node.index + 1;
        node.humble_number = humble_numbers[node.index] * node.factor;
        q.push(node);
    }

    out << humble_numbers[n] << endl;

}

