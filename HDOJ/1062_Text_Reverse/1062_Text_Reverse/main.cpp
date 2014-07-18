#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool revstr(string &str, string::size_type &start){
    string::size_type st = str.find_first_not_of(" \t", start);
    if(st == string::npos)return false;
    start = str.find_first_of(" \t", st);
    if(start == string::npos){
        reverse(str.begin()+st, str.end());
        return false;
    } else reverse(str.begin()+st, str.begin()+start);
    return true;
}

void revline(string &line){
    string::size_type st = 0;
    while(revstr(line, st));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n;
    string line;
    line.reserve(1001);
    cin>>n;
    cin.ignore(1001, '\n');
    while(n--){
        getline(cin, line);
        revline(line);
        cout<<line<<'\n';
    }
}
