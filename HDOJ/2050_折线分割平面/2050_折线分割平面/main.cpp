#include<iostream>
using namespace std;
int main(){
    int n, c;
    cin >> c;
    while(c--){
        cin >> n;
        cout << 2*n*n - n + 1 << '\n';
    }
}
