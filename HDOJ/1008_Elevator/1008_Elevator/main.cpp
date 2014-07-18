#include<iostream>
using namespace std;
int main(){
    int n, last, floor, sum;
    while(cin>>n && n){
        sum = 0;
        last = 0;
        while(n--){
            cin >> floor;
            sum += ((floor>last)? (floor-last)*6:(last-floor)*4) + 5;
            last = floor;
        }
        cout << sum << '\n';
    }
}
