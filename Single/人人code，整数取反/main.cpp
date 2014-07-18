#include<iostream>
using namespace std;
int reverse(int n){
//  Ö÷´úÂëÇø
    bool minus = false;
    if(n < 0){
        minus = true;
        n = -n;
    }
    int r = 0, d;
    while(n != 0){
        d = n % 10;
        r = r*10+d;
        n /= 10;
    }
    if(minus) r = -r;
    return r;
}

int main(){
    cout << reverse(123) << endl;
    cout << reverse(-445566) << endl;
    cout << reverse(-2147483412) << endl;
    system("pause");
}