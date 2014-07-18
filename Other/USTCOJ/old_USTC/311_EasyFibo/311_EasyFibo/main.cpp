#include<iostream>
using namespace std;
int main(){
    unsigned idx;
    int ans[]={0,1,2,1};
    while(cin>>idx)cout<<"The New Fibonacci number for "<<idx<<" is "<<ans[idx%4]<<'\n';
    return 0;
}