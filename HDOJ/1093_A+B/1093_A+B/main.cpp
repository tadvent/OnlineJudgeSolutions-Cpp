#include<iostream>
using namespace std;
int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int sum, b, n, N;
    cin>>N;
    while(N--){
        sum = 0;
        cin>>n;
        while(n--){
            cin >> b;
            sum += b;
        }
        cout<< sum << '\n';
    }
}
