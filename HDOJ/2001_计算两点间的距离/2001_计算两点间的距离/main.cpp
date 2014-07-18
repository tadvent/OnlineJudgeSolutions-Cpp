#include<iostream>
#include<complex>
using namespace std;
int main(){
    double x1,y1,x2,y2;
    cout.setf(ios::fixed);
    cout.precision(2);
    while(cin>>x1>>y1>>x2>>y2){
        complex<double> p1(x1,y1), p2(x2,y2);
        cout<<abs(p1-p2)<<'\n';
    }
}