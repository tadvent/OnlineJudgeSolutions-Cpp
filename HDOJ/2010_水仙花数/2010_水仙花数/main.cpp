#include<iostream>
#include<algorithm>
using namespace std;
bool water(int num){
    int sum=0;
    div_t d=div(num, 10);
    while(d.rem||d.quot){
        sum+=d.rem*d.rem*d.rem;
        d=div(d.quot,10);
    }
    if(num==sum)return true;
    return false;
}
int main(){
    int m, n;
    bool first;
    while(cin>>m>>n){
        first = true;
        if(m>n)swap(m,n);
        for(int i=m; i<=n; ++i){
            if(water(i)){
                if(first)first=false;
                else cout<<' ';
                cout<<i;
            }
        }
        if(first)cout<<"no";
        cout<<'\n';
    }
    cout.flush();
}