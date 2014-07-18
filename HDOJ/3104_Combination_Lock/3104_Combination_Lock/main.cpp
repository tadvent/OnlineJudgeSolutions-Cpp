#include<iostream>
using namespace std;
int main(){
    int n, t1, t2, t3;
    while(cin>>n>>t1>>t2>>t3 && (n || t1 || t2 || t3))
        cout << (4*n-1 + ((t1<t2)?(t2-t1):(t2-t1+n)) + ((t2>t3)?(t2-t3):(t2-t3+n))) << '\n';
    cout << flush;
}
