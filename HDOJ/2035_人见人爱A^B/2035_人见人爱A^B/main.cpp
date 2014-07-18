#include<iostream>
using namespace std;
int main(){
    int a,b;
    while(cin>>a>>b&&a&&b){
        int c= a%=1000;
        while(--b)c=c*a%1000;
        cout<<c<<'\n';
    }
}