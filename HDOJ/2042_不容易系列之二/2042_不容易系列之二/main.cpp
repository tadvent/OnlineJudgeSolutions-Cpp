#include<iostream>
using namespace std;
int main(){
int n,a,m;
cin>>n;
while(n--){
cin>>a;
m=3;
while(a--)m=(m-1)*2;
cout<<m<<'\n';
}
}