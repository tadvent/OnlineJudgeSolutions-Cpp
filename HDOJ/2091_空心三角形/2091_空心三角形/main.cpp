#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    bool first = true;
    char pat;
    int n;
    while(cin>>pat && pat != '@'){
        cin>>n;
        if(first)first=false;
        else cout.put('\n');
        for(int i=0; i<n-1; ++i){
            cout<<setw(n-i)<<pat;
            if(i>0)cout<<setw(2*i)<<pat;
            cout.put('\n');
        }
        fill_n(ostreambuf_iterator<char>(cout), 2*n-1, pat);
        cout.put('\n');
    }
}
