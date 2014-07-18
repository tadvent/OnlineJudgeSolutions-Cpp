#include<iostream>
using namespace std;
int main(){
    int m, n, i;
    while(cin>>n>>m){
        bool first=true;
        i=1;
        while(i+m-1 < n){
            if(first)first=false;
            else cout<<' ';
            cout<<2*i+m-1;
            i+=m;
        }
        if(!first)cout<<' ';
        cout<<2*i+n-i<<'\n';
    }
}