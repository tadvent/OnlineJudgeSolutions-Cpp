#include<iostream>
using namespace std;
long long fib[51] = {0, 1};
int main(){
    int n;
    for(int i=2; i<51; ++i)fib[i] = fib[i-1] + fib[i-2];
    while(cin>>n && n >= 0)
        cout<<fib[n]<<'\n';
}
