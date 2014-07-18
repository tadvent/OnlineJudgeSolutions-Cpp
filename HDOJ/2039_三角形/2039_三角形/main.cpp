#include<iostream>
using namespace std;
int main(){
    int m;
    double a, b, c;
    cin >> m;
    while(m--){
        cin >> a >> b >> c;
        if( a + b > c + 1e-8 &&
            b + c > a + 1e-8 &&
            c + a > b + 1e-8)
            cout << "YES\n";
        else cout << "NO\n";
    }
}