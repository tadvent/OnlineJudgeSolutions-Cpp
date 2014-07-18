/*
ID: wjl1241
PROG: game1
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

vector<int> vNums;
vector< vector<int> > vvDP;

int calcMax(int st, int ed, int sum){
    int get;
    if(st>ed)return 0;
    if(st == ed)return vNums[st];
    if((get=vvDP[st][ed])!=0)return get;
    get=sum-min(calcMax(st+1,ed,sum-vNums[st]),calcMax(st,ed-1,sum-vNums[ed]));
    vvDP[st][ed]=get;
    return get;
}

int main(){
    ifstream fin("game1.in");
    ofstream fout("game1.out");
    int N,sum=0;
    fin>>N;
    vNums.resize(N);
    vvDP.resize(N,vector<int>(N,0));
    for(int i=0;i<N;++i){
        fin>>vNums[i];
        sum+=vNums[i];
    }
    fout<<calcMax(0,N-1,sum)<<' '<<sum-calcMax(0,N-1,sum)<<endl;
}