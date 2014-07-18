#include<iostream>
using namespace std;
long long a[21] = {0, 1, 3};
int main(){
    for(int i=3; i<21; ++i)
        a[i] = a[i-1]/i*2*(i+1);
    int n, t;
    cin>>t;
    while(t--){
        cin>>n;
        cout<<a[n]<<'\n';
    }
}
