#include<iostream>
using namespace std;
int main(){
    int nfibo[41]={0,1,2};
    for(int i=3;i<41;++i)nfibo[i]=nfibo[i-1]+nfibo[i-2]+nfibo[i-3];
    int in;
    while(cin>>in)cout<<"The New Fibonacci number for "<<in<<" is "<<nfibo[in]<<'\n';
    return 0;
}