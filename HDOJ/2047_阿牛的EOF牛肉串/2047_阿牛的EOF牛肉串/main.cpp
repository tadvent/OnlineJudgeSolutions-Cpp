#include<iostream>
using namespace std;
long long a[41] = {0, 3};
long long c[41] = {0, 1};
int main(){
    for(int i=2; i<41; ++i){
        a[i] = 3*a[i-1] - c[i-1];
        c[i] = a[i-1] - c[i-1];
    }

    int n;
    while(cin>>n && n > 0 && n < 41)
        cout << a[n] << '\n';
}
