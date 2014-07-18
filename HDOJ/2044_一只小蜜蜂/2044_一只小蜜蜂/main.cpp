#include<iostream>
using namespace std;
long long arr[50] = {1,1};
int main(){
    for(int i=2; i<50; ++i)
        arr[i] = arr[i-1] + arr[i-2];
    int n, a, b;
    cin >> n;
    while(n--){
        cin >> a >> b;
        cout << arr[b-a] << '\n';
    }
}