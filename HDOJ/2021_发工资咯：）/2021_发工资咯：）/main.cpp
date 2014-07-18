#include<iostream>
#include<cstdlib>
using namespace std;
int a[] = {100, 50, 10, 5, 2, 1};
int sheet(int wage){
    int sum = 0;
    div_t d;
    d.rem = wage;
    for(int i=0; d.rem; ++i){
        d = div(d.rem, a[i]);
        sum += d.quot;
    }
    return sum;
}
int main(){
    int n;
    while(cin>>n&&n){
        int sum=0, wage;
        while(n--){
            cin>>wage;
            sum+=sheet(wage);
        }
        cout<<sum<<'\n';
    }
}