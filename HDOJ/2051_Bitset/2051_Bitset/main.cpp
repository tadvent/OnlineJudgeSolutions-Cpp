#include<iostream>
using namespace std;
int main(){
    unsigned num;
    while(cin>>num){
        bool first=true;
        for(int i=9;i>=0;--i)
            if(first){
                if((num>>i)&1){cout<<1;first=false;}
            }else{
                cout<<((num>>i)&1);
            }
        if(first)cout<<"0\n";
        else cout<<'\n';
    }
}