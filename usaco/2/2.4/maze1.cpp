/*
ID: yuziyum1
LANG: C++
TASK: maze1
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");
    solve(fin,fout);
#endif
}

int width, height;
char maze[2*100+1][2*38+1];
char steps[100][38];

struct node{
    int row,col,depth;
    node(int i, int j, int depth)
        :row(i),col(j),depth(depth){
        }
};

void bfs(int startRow, int startCol){

    queue <node> q;
    q.push(node(startRow, startCol, 1));

    while(!q.empty()){

        node cur = q.front();
        q.pop();

        if(steps[cur.row][cur.col] != 0){
            continue;
        }

        steps[cur.row][cur.col] = cur.depth;

        for(int x = -1; x <= 1; x+=2){
            if(cur.col+x >= 0  && cur.col+x < width && maze[2*cur.row+1][2*cur.col+1+x] == ' '){
                q.push(node(cur.row,cur.col+x,cur.depth+1));
            }
            if(cur.row+x >= 0  && cur.row+x < height && maze[2*cur.row+1+x][2*cur.col+1] == ' '){
                q.push(node(cur.row+x,cur.col,cur.depth+1));
            }
        }
    }

}

void solve(istream &in,ostream &out){
    //start solve the problem
    in >> width >> height;

    char tmp;
    in.get(tmp); // '\n'

    int exits[2][2];
    int exitsCnt = 0;

    for(int i = 0; i < 2 * height + 1; ++i){
        for(int j = 0; j < 2 * width + 1; ++j) {
            in.get(maze[i][j]);
            if((i == 0 || i == 2 * height) && maze[i][j] == ' '){
                exits[exitsCnt][0] = (i == 0 ? 0 : height - 1);
                exits[exitsCnt][1] = (j - 1)/2;
                exitsCnt++;
            }else if((j == 0 || j == 2 * width) && maze[i][j] == ' '){
                exits[exitsCnt][0] = (i - 1)/2;
                exits[exitsCnt][1] = (j == 0 ? 0 : width - 1);
                exitsCnt++;
            }
        }
        in.get(tmp); // '\n'
    }

    static int totalSteps[2][100][38];
    for(int i = 0; i < exitsCnt; ++i){
        //广度优先，算两个出口到每个格子的最短距离

        queue <node> q;
        q.push(node(exits[i][0], exits[i][1], 1));

        while(!q.empty()){

            node cur = q.front();
            q.pop();

            if(totalSteps[i][cur.row][cur.col] != 0){
                continue;
            }

            totalSteps[i][cur.row][cur.col] = cur.depth;

            for(int x = -1; x <= 1; x+=2){
                if(cur.col+x >= 0  && cur.col+x < width && maze[2*cur.row+1][2*cur.col+1+x] == ' '){
                    q.push(node(cur.row,cur.col+x,cur.depth+1));
                }
                if(cur.row+x >= 0  && cur.row+x < height && maze[2*cur.row+1+x][2*cur.col+1] == ' '){
                    q.push(node(cur.row+x,cur.col,cur.depth+1));
                }
            }
        }

    }

    int result = 0;
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            if(exitsCnt == 1){
                result = max(result, totalSteps[0][i][j]);
            }else{
                result = max(result, min(totalSteps[0][i][j], totalSteps[1][i][j]));
            }
        }
    }

    out << result << endl;

}


