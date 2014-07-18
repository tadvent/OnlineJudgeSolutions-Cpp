#include<iostream>
#include<cmath>
using namespace std;
int main(){
    double a;
    cout.setf(ios::fixed);
    cout.precision(2);
    while(cin>>a)
        cout<<abs(a)<<'\n';
}