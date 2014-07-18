#include<iostream>
using namespace std;
int f(char c){
    if(c >= 'A' && c <= 'Z')return c-'A'+1;
    else if(c >= 'a' && c <= 'z')return 'a'-c-1;
    return 0;
}
int main(){
    int T, y;
    char x;
    cin>>T;
    while(T--){
        cin>>x>>y;
        cout<<y+f(x)<<'\n';
    }
}