#include<iostream>
using namespace std;
int main(){
long long n,a[51]={1,1,2};
for(int i=3;i<51;++i)a[i]=a[i-1]+a[i-2];
while(cin>>n)
cout<<a[n]<<'\n';
}
