#include<iostream>
using namespace std;

long long a[34] = {1};
long long b[34] = {0};

int main(){
    for(int i=1; i<34; ++i){
        a[i] = 3*a[i-1] + 2*b[i-1];
        b[i] = a[i-1] + b[i-1];
    }

    int n;
    while(cin>>n && n>=0){
        cout<<a[n]<<", "<<b[n]<<'\n';
    }
}
