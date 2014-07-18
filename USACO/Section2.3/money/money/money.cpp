/*
ID: wjl1241
PROG: money
LANG: C++
*/

#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> changes;
vector<vector<long long> > dpmatrix;

long long dp(int amount, int uplimit){
    long long rst;
    if((rst=dpmatrix[amount][uplimit-1])!=-1)return rst;
    rst=0;
    for(int i=uplimit-1;i>=0;--i){
        if(changes[i]>amount)continue;
        rst+=dp(amount-changes[i],i+1);
    }
    dpmatrix[amount][uplimit-1]=rst;
    return rst;
}

int main(){
    ifstream fin("money.in");
    ofstream fout("money.out");
    int v,n;
    fin>>v>>n;
    changes.resize(v);
    for(int i=0;i<v;++i)fin>>changes[i];
    sort(changes.begin(),changes.end());

    dpmatrix.resize(n+1);
    for(int i=0;i<=n;++i){
        dpmatrix[i].resize(v);
        for(int j=0;j<v;++j)dpmatrix[i][j]=-1;
    }
    for(int i=0;i<v;++i)dpmatrix[0][i]=1;

    fout<<dp(n,v)<<endl;

    return 0;
}