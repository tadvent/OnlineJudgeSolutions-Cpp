#include<iostream>
#include<cmath>
using namespace std;

int arg(int h, int m, int s){
    double arg_m = 6.0*m + double(s)/10;
    double arg_h = 30.0*(h%12) + arg_m/12.0;
    double a = abs(arg_m - arg_h);
    if(a <= 180) return int(a);
    else return int(360.0-a);
}

int main(){
    int T, h, m, s;
    cin>>T;
    while(T--){
        cin>>h>>m>>s;
        cout<<arg(h,m,s)<<'\n';
    }
}
