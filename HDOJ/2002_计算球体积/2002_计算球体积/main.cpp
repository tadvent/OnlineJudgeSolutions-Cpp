#include<iostream>
using namespace std;
const double pi=3.1415927;
int main(){
    double r;
    cout.setf(ios::fixed);
    cout.precision(3);
    while(cin>>r)
        cout<<4.0/3*pi*r*r*r<<'\n';
}