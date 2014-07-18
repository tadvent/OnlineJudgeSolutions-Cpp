#include<iostream>
#include<string>
using namespace std;

int main(){
    string l, p;
    while(cin>>l && l != "#"){
        cin>>p;
        int cnt = 0;
        string::size_type last = 0;
        for(;;){
            last = l.find(p, last);
            if(last == string::npos)break;
            ++cnt;
            last += p.length();
        }
        cout<<cnt<<'\n';
    }
}
