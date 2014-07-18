#include<iostream>
#include<numeric>
using namespace std;
double a[1001]={0.0};
int main(){
    double sign=1.0;
    for(int i=1;i<1001;++i){
        a[i]=sign*1/i;
        sign *= -1;
    }
    partial_sum(a, a+1001, a);
    int m,n;
    cout.setf(ios::fixed);
    cout.precision(2);
    cin>>m;
    while(m--){
        cin>>n;
        cout<<a[n]<<'\n';
    }
}