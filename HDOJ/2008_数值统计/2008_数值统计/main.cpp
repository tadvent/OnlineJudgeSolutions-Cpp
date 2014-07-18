#include<iostream>
using namespace std;
int main(){
    int n, a, b, c;
    double num;
    while(cin>>n&&n){
        a=b=c=0;
        while(n--){
            cin>>num;
            if(num<0)++a;
            else if(num>0)++c;
            else ++b;
        }
        cout<<a<<' '<<b<<' '<<c<<'\n';
    }
}