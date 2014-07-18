/*
ID: wjl1241
LANG: C++
TASK: milk4
*/

// dfsid + dfs
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> tmpPails;
vector<int> tmpidxs;
vector<int> pails;
int Q;

bool isValid(int qt, int *pnum, int n){
    if(qt == 0)return true;
    if(n == 0)return false;
    if(n == 1)return qt%(*pnum) == 0;
    qt -= *pnum;
    while(qt >= 0){
        if(isValid(qt, pnum+1, n-1))return true;
        qt -= *pnum;
    }
    return false;
}

bool dfsid(int deep){
    if(deep == 0){
        tmpPails.clear();
        for(int i=0; i<(int)tmpidxs.size(); ++i)
            tmpPails.push_back(pails[tmpidxs[i]]);
        return isValid(Q, &tmpPails[0], tmpPails.size());
    }
    for(int i=(tmpidxs.empty()?0:tmpidxs.back()+1); i<(int)pails.size(); ++i){
        tmpidxs.push_back(i);
        if(dfsid(deep-1))return true;
        tmpidxs.pop_back();
    }
    return false;
}

void calc(){
    for(int d=1;;++d){
        tmpidxs.clear();
        if(dfsid(d))break;
    }
}

int main(){
    int p, vol;
    FILE *fin, *fout;
    fin = fopen("milk4.in", "r");
    fscanf(fin, "%d%d", &Q, &p);
    while(p--){
        fscanf(fin, "%d", &vol);
        pails.push_back(vol);
    }
    fclose(fin);

    sort(pails.begin(), pails.end());
    calc();

    fout = fopen("milk4.out", "w");
    fprintf(fout, "%d", tmpPails.size());
    for(int i=0; i<(int)tmpPails.size(); ++i)
        fprintf(fout, " %d", tmpPails[i]);
    fputc('\n', fout);
    fclose(fout);
}
