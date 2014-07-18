#include<iostream>
using namespace std;
inline bool divid(int n){
    const static bool a[] = {0,0,1,0,0,0,1,0};
    return a[n%(sizeof(a)/sizeof(a[0]))];
}
int main(){
    int n;
    while(cin>>n && n>=0){
        cout<<(divid(n)? "yes\n":"no\n");
    }
}
