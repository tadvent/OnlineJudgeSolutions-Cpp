#include<iostream>
#include<cmath>
using namespace std;

inline double ptarg(double x1, double y1, double x2, double y2){
    double a = abs(atan2(y1, x1) - atan2(y2, x2)) * 180.0/acos(-1.0);
    return (a <= 180.0)? a:(360.0-a);
}

int main(){
    int t;
    double x1, y1, x2, y2;
    cout.setf(ios::fixed);
    cout.precision(2);
    cin>>t;
    while(t--){
        cin>>x1>>y1>>x2>>y2;
        cout<<ptarg(x1,y1,x2,y2)<<'\n';
    }
}
