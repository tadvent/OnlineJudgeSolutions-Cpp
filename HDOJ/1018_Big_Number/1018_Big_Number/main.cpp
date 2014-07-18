#include<iostream>
#include<cmath>
using namespace std;

int digits(int num){
    double sum = 0.0;
    const double d = log(10.0);
    for(int i = 2; i <= num; ++i)
        sum += log(double(i));
    return int(sum/d + 1e-4) + 1;
}

int main(){
    int n, num;
    cin >> n;
    while(n--){
        cin >> num;
        cout << digits(num) << '\n';
    }
}
