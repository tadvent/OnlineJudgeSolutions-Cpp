#include<iostream>
using namespace std;
long a[56]={1,1,2};
int main(){
    int i;
    for(i=3;i<56;++i)a[i]=a[i-1]+a[i-3];
    while(cin>>i&&i)cout<<a[i]<<'\n';
}