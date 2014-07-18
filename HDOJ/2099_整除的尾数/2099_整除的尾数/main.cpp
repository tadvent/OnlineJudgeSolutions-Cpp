#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    int a,b;
    cout.fill('0');
    while(cin>>a>>b && a && b){
        int rem = (a*100) % b;
        if(rem)rem = b - rem;
        cout<<setw(2)<<rem;
        while((rem += b) < 100)cout<<' '<<setw(2)<<rem;
        cout<<'\n';
    }
}
