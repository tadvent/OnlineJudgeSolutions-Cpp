#include<iostream>
using namespace std;

int gcd(int a, int b){
    if(a<b)swap(a,b);
    while(b){
        int rem = a%b;
        a = b;
        b = rem;
    }
    return a;
}

int findc(int a, int b){
    int c = b+b;
    while(gcd(a, c) != b)
        c += b;
    return c;
}

int main(){
    int t, a, b;
    cin>>t;
    while(t--){
        cin>>a>>b;
        cout<<findc(a,b)<<'\n';
    }
}
