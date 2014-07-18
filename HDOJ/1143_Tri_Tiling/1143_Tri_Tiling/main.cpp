#include<iostream>
using namespace std;
int nums[16]={1, 3};
void init(){
    int sum = 0;
    for(int i=2; i<16; ++i){
        sum += 2*nums[i-2];
        nums[i] = 3*nums[i-1] + sum;
    }
}
int main(){
    int n;
    init();
    while(cin>>n && n!=-1){
        if(n%2)cout<<"0\n";
        else cout<<nums[n/2]<<'\n';
    }
}
