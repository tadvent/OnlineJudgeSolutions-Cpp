#include<iostream>
using namespace std;
int main(){
    int a,b,t;
    cin>>t;
    while(t--){
        cin>>a>>b;
        cout<<(a%100 + b%100)%100<<'\n';
    }
}
