#include<iostream>
#include<cmath>
using namespace std;
int main(){
    double n;
    int m;
    cout.setf(ios::fixed);
    cout.precision(2);
    while(cin>>n>>m){
        double sum=0.0;
        while(m--){
            sum+=n;
            n=sqrt(n);
        }
        cout<<sum<<'\n';
    }
}