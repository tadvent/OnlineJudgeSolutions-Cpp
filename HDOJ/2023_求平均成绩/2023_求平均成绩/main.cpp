#include<iostream>
#include<cstring>
using namespace std;
int m,n;
int score[50][5];
double avecs[5];
double avest[50];
int aboveave(){
    int num=0;
    for(int i=0;i<n;++i){
        int j;
        for(j=0;j<m;++j)if(score[i][j]<avecs[j]-1e-8)break;
        if(j==m)++num;
    }
    return num;
}
int main(){
    cout.setf(ios::fixed);
    cout.precision(2);
    while(cin>>n>>m){
        memset(avecs,0,sizeof(avecs));
        memset(avest,0,sizeof(avest));
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                cin>>score[i][j];
                avest[i]+=score[i][j];
                avecs[j]+=score[i][j];
            }
            avest[i]/=m;
        }
        for(int j=0;j<m;++j)avecs[j]/=n;
        for(int i=0;i<n-1;++i)cout<<avest[i]<<' ';
        cout<<avest[n-1]<<'\n';
        for(int j=0;j<m-1;++j)cout<<avecs[j]<<' ';
        cout<<avecs[m-1]<<'\n'<<aboveave()<<"\n\n";
    }
}
