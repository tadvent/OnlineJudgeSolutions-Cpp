#include<iostream>
using namespace std;
int main(){
    int n, num, result;
    while(cin>>n){
        result=1;
        while(n--){
            cin>>num;
            if(num%2)result*=num;
        }
        cout<<result<<'\n';
    }
}