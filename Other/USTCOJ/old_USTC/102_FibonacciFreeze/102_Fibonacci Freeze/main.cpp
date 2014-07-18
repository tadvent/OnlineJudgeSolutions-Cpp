#include<iostream>
using namespace std;
int main(){
    int fibo[41]={0,1};
    for(int i=2;i<41;++i)fibo[i]=fibo[i-1]+fibo[i-2];
    int in;
    while(cin>>in)cout<<"The Fibonacci number for "<<in<<" is "<<fibo[in]<<endl;
    return 0;
}