#include<iostream>
using namespace std;
int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int sum, b, n;
    while(cin>>n && n!=0){
        sum = 0;
        while(n--){
            cin >> b;
            sum += b;
        }
        cout<< sum << '\n';
    }
}