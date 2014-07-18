#include<iostream>
using namespace std;

int main(){
    int n;
    double a0, an1, sum;
    cout.setf(ios::fixed);
    cout.precision(2);
    while(cin>>n){
        cin>>a0>>an1;
        sum = n*a0 + an1;
        for(int i=0; i<n; ++i){
            cin>>a0;
            sum -= 2*(n-i)*a0;
        }
        cout<<(sum/(n+1))<<'\n';
    }
}
