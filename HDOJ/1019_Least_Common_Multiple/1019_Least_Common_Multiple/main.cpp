#include<iostream>
#include<algorithm>
using namespace std;
long long ggg(long long a, long long b){
    long long m=a,n=b;
    if(a<b)swap(a,b);
    long long c=a%b;
    while(c){
        a=b;b=c;c=a%b;
    }
    return m*n/b;
}
int main(){
    int m,n;
    cin>>m;
    while(m--){
        cin>>n;
        long long max=1,num;
        while(n--){
            cin>>num;
            max=ggg(max,num);
        }
        cout<<max<<'\n';
    }
}
