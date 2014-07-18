#include<iostream>
using namespace std;
int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int N, a, b;
    cin>>N;
    while(N--){
        cin>>a>>b;
        cout<<a+b<<'\n';
    }
}
