#include<iostream>
using namespace std;
const int n = 9;
int main(){
    double inv = 1.0, sum = 1.0;
    cout << "n e\n- -----------\n";
    cout.precision(10);
    for(int i = 0; i <= n; ++i){
        if(i==3){
            cout.setf(ios::fixed);
            cout.precision(9);
        }
        cout << i << ' ' << sum << '\n';
        inv /= double(i + 1);
        sum += inv;
    }
}
