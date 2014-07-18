/*
ID: wjl1241
PROG: subset
LANG: C++
*/

//This is a classic dynamic programming problem. 

#include<fstream>
#include<vector>
using namespace std;

vector<vector<unsigned long> > known;

unsigned long calc(int n,int cap){
    if(known[n][cap]!=~0)return known[n][cap];
    if(cap<n){
        known[n][cap]=calc(n-1,cap);
    }
    else {
        known[n][cap]=calc(n-1,cap)+calc(n-1,cap-n);
    }
    return known[n][cap];
}

int main(){
    ifstream fin("subset.in");
    ofstream fout("subset.out");

    int n;
    fin>>n;
    int sum=(1+n)*n/2;
    if(sum&1){//sum is odd, then print 0
        fout<<0<<endl;
        return 0;
    }
    sum>>=1;
    known.resize(n+1);
    for(int i=0;i<=n;++i){
        known[i].resize(sum+1);
        known[i][0]=1;
        for(int j=1;j<=sum;++j)
            known[i][j]=~0;
    }
    for(int i=1;i<=sum;++i)known[0][i]=0;

    fout<<calc(n,sum)/2<<endl;
    return 0;
}