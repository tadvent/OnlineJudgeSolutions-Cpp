#include<iostream>
#include<string>
using namespace std;
int count(const string &s){
    int cnt=0;
    for(string::const_iterator it=s.begin();it!=s.end();++it)if(*it<0){++cnt;++it;}
    return cnt;
}
int main(){
    string s;
    int n;
    cin>>n;
    cin.ignore(INT_MAX,'\n');
    while(n--){
        getline(cin,s);
        cout<<count(s)<<'\n';
    }
}