/*
ID: wjl1241
PROG: fence
LANG: C++
*/

#include<fstream>
#include<vector>
#include<stack>
using namespace std;

int fence[500][500];
int lower=1000,upper=0;
vector<int> vCircuit;

void FindCircuit(int s){
    for(int i=lower;i<=upper;++i)if(fence[s][i]){
        --fence[s][i];--fence[i][s];
        FindCircuit(i);
    }
    vCircuit.push_back(s);
}

int main(){
    ifstream fin("fence.in");
    ofstream fout("fence.out");
    for(int i=0;i<500;++i)for(int j=0;j<500;++j)fence[i][j]=0;
    int nFence;
    fin>>nFence;
    for(int i=0;i<nFence;++i){
        int u,v;
        fin>>u>>v;--u;--v;
        ++fence[u][v];
        ++fence[v][u];
        lower=min(lower,u);
        lower=min(lower,v);
        upper=max(upper,u);
        upper=max(upper,v);
    }
    int start;
    for(start=lower;start<=upper;++start){
        int degree=0;
        for(int i=lower;i<=upper;++i)if(fence[start][i])degree+=fence[start][i];
        if(0 != degree%2)break;
    }
    if(start>upper)start=lower;

    FindCircuit(start);
    for(int i=(int)vCircuit.size()-1;i>=0;--i)fout<<vCircuit[i]+1<<'\n';
}