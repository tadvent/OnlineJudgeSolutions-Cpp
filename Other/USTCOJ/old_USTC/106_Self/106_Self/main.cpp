#include<iostream>
using namespace std;
int d(int n){
    int a=0,b=n;
    for(int i=0;i<4;++i){
        a+=n%10;
        n/=10;
    }
    return a+b;
}
bool isSelf(int n){
    int start=(n-36>0)?(n-36):0;
    for(int i=start;i<n;++i)if(d(i)==n)return false;
    return true;
}
int main(){
    for(int i=1;i<10000;++i)if(isSelf(i))cout<<i<<'\n';
    return 0;
}