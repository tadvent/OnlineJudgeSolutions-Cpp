#include<iostream>
#include<string>
#include<utility>
using namespace std;
pair<int,int> border(const string &s){
    string::size_type b, e;
    b = s.find_first_not_of('0');
    if(b == string::npos)return pair<int,int>(0, 0);
    e = s.find('.', b);
    if(e == string::npos)return pair<int,int>(b, s.size()-b);
    e = s.find_last_not_of('0');
    if(s[e] != '.')++e;
    return pair<int,int>(b, e-b);
}
bool equ(const string &s1, const string &s2){
    pair<int, int> bord1, bord2;
    bord1 = border(s1);
    bord2 = border(s2);
    return s1.compare(bord1.first, bord1.second, s2, bord2.first, bord2.second) == 0;
}
int main(){
    string a, b;
    while(cin>>a>>b)
        cout<<(equ(a,b)?"YES":"NO")<<'\n';
}
