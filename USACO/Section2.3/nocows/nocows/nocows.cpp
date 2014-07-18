/*
ID: wjl1241
PROG: nocows
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

vector< vector<long> > MyCount;

long calc(int n, int k){
    long cnt;
    int mid=n/2;
    if((cnt=MyCount[n][k])!=-1)return cnt;
    cnt=0;
    for(int idx=1;idx<mid;++idx)cnt+=calc(idx,k-1)*calc(n-1-idx,k-1);
    cnt<<=1;
    if(n&0x1)cnt+=calc(mid,k-1)*calc(mid,k-1);
    cnt%=9901;
    MyCount[n][k]=cnt;
    return cnt;
}

int main(){
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");

    int n,k;
    fin>>n>>k;

    MyCount.resize(n+1);
    for(int i=0;i<=n;++i){
        MyCount[i].resize(k+1);
        for(int j=0;j<=k;++j)MyCount[i][j]=-1;
    }
    for(int i=0;i<=n;++i)MyCount[i][0]=0;
    for(int j=1;j<=k;++j){
        MyCount[0][j]=0;
        MyCount[1][j]=1;
    }

    int result=calc(n,k)-calc(n,k-1);
    if(result<0)result+=9901;
    fout<<result<<endl;

    return 0;
}