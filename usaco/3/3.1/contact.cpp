/*
ID: yuziyum1
LANG: C++
TASK: contact
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void solve(istream &,ostream &);

int main(){
#ifdef _DEV_
    solve(cin,cout);
#else
    ifstream fin("contact.in");
    ofstream fout("contact.out");
    solve(fin,fout);
#endif
}

char sequence[200001];
char buf[81];

struct pattern_node{
    int cnt;
    string *pattern;
    bool operator> (const pattern_node &other) const{
        if(this->cnt != other.cnt){
            return this->cnt > other.cnt;
        }
        int size1 = this->pattern->size();
        int size2 = other.pattern->size();
        if(size1 == size2){
            return *this->pattern < *other.pattern;
        }else{
            return size1 < size2;
        }
    }
};

vector<pattern_node> patterns;

struct trie_node{
    int cnt;
    trie_node* children[2];
    trie_node() {
        cnt = 0;
        children[0] = children[1] = NULL;
    }
};

void build_trie(trie_node *root, const char *seq, int len) {
    trie_node *cur;
    int child_index;
    for(int i = 0; seq[i+len-1] != '\0'; ++i){
        cur = root;
        for(int j = 0; j < len; ++j) {
            child_index = seq[i+j]-'0';
            if(cur->children[child_index] == NULL){
                cur->children[child_index] = new trie_node;
            }
            cur = cur->children[child_index];
        }
        cur->cnt++;
    }
}

void dfs(trie_node *root, int depth){

    static char buf[12];

    if(!root){
        return;
    }

    int childCnt = 0;
    for(int i = 0; i < 2; ++i){
        if(root->children[i]){
            childCnt++;
            buf[depth] = '0'+i;
            dfs(root->children[i], depth+1);
        }
    }

    if(!childCnt && root->cnt != 0){
        //leaf node
        pattern_node node;
        node.cnt = root->cnt;
        node.pattern = new string(buf);
        patterns.push_back(node);
    }
}

void solve(istream &in,ostream &out){

    //start solve the problem
    int minPatternLen, maxPatternLen, topNum;
    in >> minPatternLen >> maxPatternLen >> topNum;

    int seqLen = 0;
    string row;
    char *pointer = sequence;
    while(in >> row){
        strcat(sequence, row.c_str());
    }

    trie_node trees[maxPatternLen-minPatternLen+1];
    for(int i = minPatternLen; i <= maxPatternLen; ++i) {
        build_trie(&trees[i-minPatternLen], sequence, i);
        dfs(&trees[i-minPatternLen], 0);
    }

    sort(patterns.begin(), patterns.end(), greater<pattern_node>());
    int sameCntNumber = 0;
    int lastCnt = -1;
    for(vector<pattern_node>::iterator i = patterns.begin();
            i != patterns.end(); ++i){
        if(lastCnt != i->cnt) {
            if(topNum == 0){
                break;
            }
            topNum--;
            sameCntNumber = 1;
            if(lastCnt != -1){
                out << endl;
            }
            lastCnt = i->cnt;
            out << i->cnt;
        }else{
            sameCntNumber++;
        }
        out << (sameCntNumber % 6 == 1 ? '\n' : ' ') << *i->pattern;
    }
    out << endl;

}

