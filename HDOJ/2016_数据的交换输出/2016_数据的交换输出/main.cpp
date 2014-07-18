#include<iostream>
#include<algorithm>
using namespace std;
int num[101];
int main(){
    int n;
    while(cin>>n&&n){
        int min=0;
        for(int i=0; i<n; ++i){
            cin>>num[i];
            if(num[i]<num[min])min=i;
        }
        swap(num[0],num[min]);
        for(int i=0; i<n-1; ++i)cout<<num[i]<<' ';
        cout<<num[n-1]<<'\n';
    }
}