#include<iostream>
using namespace std;
int nums[34];
void fillnums(int n){
    for(int i=0;i<34;++i)nums[i]=0;
    nums[1] = 1;
    for(int i=0;i<n;++i){
        for(int j=1; j<i+1; ++j)cout<<nums[j]<<' ';
        cout<<nums[i+1]<<'\n';
        for(int j=i+2;j>0;--j)nums[j] += nums[j-1];
    }
    cout.put('\n');
}
int main(){
    int n;
    while(cin>>n)fillnums(n);
}