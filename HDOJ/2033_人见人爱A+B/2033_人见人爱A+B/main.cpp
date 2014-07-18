#include<iostream>
using namespace std;
int main(){
    int a1,a2,a3,b1,b2,b3,n;
    cin>>n;
    while(n--){
        cin>>a1>>a2>>a3>>b1>>b2>>b3;
        a1+=b1;a2+=b2;a3+=b3;
        while(a3>=60){
            ++a2;
            a3-=60;
        }
        while(a2>=60){
            ++a1;
            a2-=60;
        }
        cout<<a1<<' '<<a2<<' '<<a3<<'\n';
    }
}