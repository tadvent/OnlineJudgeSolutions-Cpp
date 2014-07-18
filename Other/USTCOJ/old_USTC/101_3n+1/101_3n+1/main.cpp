#include<iostream>
using namespace std;
void next(long &n){
    if(n==1)n=0;
    else if(n%2==0)n/=2;
    else n=3*n+1;
}
long calcyc(long n){
    long cyc=0;
    while(n){
        ++cyc;
        next(n);
    }
    return cyc;
}
int main(){
    long a,b;
    while(cin>>a>>b){
        cout<<a<<' '<<b<<' ';
        if(a>b)swap(a,b);
        long longcyc=0;
        for(long i=a;i<=b;++i){
            long temp=calcyc(i);
            if(temp>longcyc)longcyc=temp;
        }
        cout<<longcyc<<'\n';
    }
    return 0;
}