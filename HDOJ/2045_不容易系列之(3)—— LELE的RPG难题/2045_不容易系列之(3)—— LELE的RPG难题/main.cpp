#include<iostream>
using namespace std;
long long a[50] = {3,6,6};
int main(){
    for(int i=3; i<50; ++i)
        a[i] = a[i-1] + 2*a[i-2];
    int n;
    while(cin>>n)
        cout<<a[n-1]<<'\n';
}