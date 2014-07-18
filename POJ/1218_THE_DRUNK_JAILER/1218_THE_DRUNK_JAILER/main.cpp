#include<fstream>
#include<iostream>
#include<cmath>
using namespace std;

int cal(int n){
    return static_cast<int>(sqrt((double)n));
}

int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    int num;
    cin>>num;
    while(num--){
        int n;
        cin>>n;
        cout<<cal(n)<<'\n';
    }
}
