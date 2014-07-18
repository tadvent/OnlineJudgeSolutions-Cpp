#include<iostream>
using namespace std;
int main(){
    int n;
    float x;
    cout.setf(ios::hex, ios::basefield);
    cout.setf(ios::uppercase);
    cin>>n;
    while(n--){
        cin>>x;
        cout << reinterpret_cast<long&>(x) << '\n';
    }
}
