/*
ID: wjl1241
PROG: ariprog
LANG: C
*/

#include<stdio.h>
//#include<fstream>
//#include<vector>
//#include<set>
//#include<algorithm>
//using namespace std;

#define MAXN 125001
#define bool int
#define true 1
#define false 0

//bool check(int a, int b, const set<int> &bis, int n){
//bool check(int a, int b, const vector<int> &bis, int n){
bool check(int a, int b, int bis[], int n){
    int i=0;
    for(;i<n;++i,a+=b)
        //if(bis.find(a+b*i)==bis.end())return false;
        if(0==bis[a])return false;
    return true;
}

int main(){
    //ifstream fin("ariprog.in");
    //ofstream fout("ariprog.out");
    FILE *fin,*fout;
    fin=fopen("ariprog.in","r");
    fout=fopen("ariprog.out","w");
    //set<int> bisqure;
    //vector<int> bisqure;
    //vector<int> squre;
    int bisqure[MAXN];
    int squre[251];

    int N,M;
    //fin>>N>>M;
    fscanf(fin,"%d %d",&N,&M);
    //bisqure.resize(M*M*2+1,0);
    //squre.resize(M+1);
    int i,j;
    for(i=0;i<=M;++i)squre[i]=i*i;
    for(i=0;i<MAXN;++i)bisqure[i]=0;
    for(i=0;i<=M;++i)for(j=i;j<=M;++j)
        //bisqure.insert(squre[i]+squre[j]);
        bisqure[squre[i]+squre[j]]=1;

    int mb=(squre[M]+squre[M])/(N-1);
    bool nout=true;

    for(i=1;i<=mb;++i){
        int ma=squre[M]+squre[M]-i*(N-1);
        for(j=0;j<=ma;++j){
            if(check(j,i,bisqure,N)){
                //fout<<a<<' '<<b<<'\n';
                fprintf(fout,"%d %d\n",j,i);
                if(nout)nout=false;
            }
        }
    }

    if(nout)
        //fout<<"NONE"<<endl;
        fprintf(fout,"NONE\n");

    //fout<<(M+1)*(M+2)/2<<' '<<bisqure.size()<<endl;
    //for(set<int>::iterator i=bisqure.begin();i!=bisqure.end();++i)
    //    fout<<(*i)<<' ';

    return 0;
}
