/*
ID: wjl1241
PROG: rockers
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;
const int maxnum=25;

int nSongs,nTime,nDiscs;
vector<int> vLen;

int DP[maxnum][maxnum][maxnum]={-1};

int dp(int a, int b, int c){
    int result;
    if((result=DP[a][b][c])!=-1)return result;
    result=dp(a,b,c-1);
    if(b>=vLen[c])result=max(result,dp(a,b-vLen[c],c-1)+1);
    else if(a>0 && nTime>=vLen[c])result=max(result,dp(a-1,nTime-vLen[c],c-1)+1);
    DP[a][b][c]=result;
    return result;
}

int main(){
    ifstream fin("rockers.in");
    ofstream fout("rockers.out");
    fin>>nSongs>>nTime>>nDiscs;
    vLen.resize(nSongs+1);
    for(int i=1;i<=nSongs;++i)fin>>vLen[i];

    for(int i=0;i<maxnum;++i)for(int j=0;j<maxnum;++j){
        DP[i][j][0]=0;
        for(int k=1;k<maxnum;++k)DP[i][j][k]=-1;
    }

    fout<<dp(nDiscs-1,nTime,nSongs)<<endl;
}
