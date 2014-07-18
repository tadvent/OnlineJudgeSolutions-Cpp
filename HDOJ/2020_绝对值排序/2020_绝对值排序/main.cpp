#include<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;
int a[101],n;
inline bool gt(int a, int b){return abs(a)>abs(b);}
int main(){
    while(cin>>n&&n){
        for(int i=0;i<n;++i)cin>>a[i];sort(a,a+n,gt);
        for(int i=0;i<n-1;++i)cout<<a[i]<<' ';
        cout<<a[n-1]<<'\n';
    }
}