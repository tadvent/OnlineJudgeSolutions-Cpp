// 又是一道题目叙述不清的垃圾题

#include<iostream>
using namespace std;

int main(){
    int t, n, m, a, min;
    cin>>t;
    while(t--){
        cin>>n>>m;
        min = 100;
        while(n--){
            cin>>a;
            if(a<min)min=a;
        }
        cout<<(100-min)*(100-min)<<'\n';
    }
}
