#include<iostream>
using namespace std;
int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int a, b;
    while(cin>>a>>b && (a!=0 || b!=0)){
        cout<<a+b<<'\n';
    }
}
