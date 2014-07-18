#include<iostream>
#include<algorithm>
using namespace std;
int gcd(int a, int b){ // a >= b
    int c = a%b;
    while(c){
        a=b;b=c;c=a%b;
    }
    return b;
}
int main(){
    int a, b;
    while(cin>>a>>b){
        if(a<b)swap(a,b);
        cout<<a*b/gcd(a,b)<<'\n';
    }
}
