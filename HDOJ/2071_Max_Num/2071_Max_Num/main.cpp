#include<iostream>
using namespace std;
int main(){
    int t, n;
    double max, current;
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    cin >> t;
    while(t--){
        max = 0.0;
        cin >> n;
        while(n--){
            cin >> current;
            if(current > max) max = current;
        }
        cout << max << '\n';
    }
}
