#include<iostream>
using namespace std;

long long a[36] = {0};

void init(){
    for(int i=1; i<36; ++i)
        a[i] = 2 + 3 * a[i-1];
}

int main(){
    int n;
    init();
    while(cin>>n && n>0){
        cout<<a[n]<<'\n';
    }
}
