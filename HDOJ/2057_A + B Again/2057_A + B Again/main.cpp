#include<iostream>
using namespace std;
int main(){
    long long a, b;
    cin.setf(ios::hex, ios::basefield);
    cout.setf(ios::hex, ios::basefield);
    cout.setf(ios::uppercase);
    while(cin>>a>>b){
        long long c = a+b;
        if(c<0){cout<<'-';c=-c;}
        cout<<c<<'\n';
    }
}
