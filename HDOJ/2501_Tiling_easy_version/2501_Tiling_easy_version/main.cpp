#include<iostream>
using namespace std;
long long a[31] = {1,1,3};
int main(){
    for(int i=3; i<31; ++i)
        a[i] = a[i-1] + 2*a[i-2];
    int t, n;
    cin>>t;
    while(t--){
        cin>>n;
        cout<<a[n]<<'\n';
    }
}
