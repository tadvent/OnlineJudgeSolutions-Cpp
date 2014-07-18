#include<iostream>
using namespace std;
unsigned long long a[31]={1};
void init(){
    for(int i=1; i<31; ++i)a[i]=2*(a[i-1]+1);
}
int main(){
    int n;
    init();
    while(cin>>n)
        cout<<a[n-1]<<'\n';
}