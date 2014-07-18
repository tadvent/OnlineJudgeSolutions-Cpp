#include<iostream>
using namespace std;
int main(){
    freopen("i.txt", "r", stdin);
    int n;
    char c;
    cin>>n;
    cin.ignore(100, '\n');
    while(n--){
        int num=0;
        while(cin.get(c) && c!='\n')if(c>='0'&&c<='9')++num;
        cout<<num<<'\n';
    }
}