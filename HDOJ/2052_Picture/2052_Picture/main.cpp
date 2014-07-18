#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    int w, h;
    while(cin>>w>>h && w>=0 && h>=0){
        cout<<'+'<<setfill('-')<<setw(w+1)<<'+'<<'\n';
        cout.fill(' ');
        while(h--)cout<<'|'<<setw(w+1)<<'|'<<'\n';
        cout<<'+'<<setfill('-')<<setw(w+1)<<'+'<<"\n\n";
    }
}
