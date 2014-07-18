#include<iostream>
#include<string>
using namespace std;
bool isHui(const string &s){
    if(s.empty())return true;
    string::const_iterator itl=s.begin(), itr=s.end()-1;
    while(itl<itr)if(*itl++!=*itr--)return false;
    return true;
}
int main(){
    string str;
    int n;
    cin>>n;
    while(n--){
        cin>>str;
        if(isHui(str))cout<<"yes\n";
        else cout<<"no\n";
    }
}