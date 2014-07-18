#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
bool prime[2600]={0,0,1};
void init(){
    for(int i=3;i<2600;i+=2){
        int root=(int)sqrt(double(i)+1e-8);
        bool pr=true;
        for(int j=3;j<=root&&pr;j+=2)if(prime[j]&&i%j==0)pr=false;
        prime[i]=pr;
    }
}
int main(){
    int x, y;
    init();
    while(cin>>x>>y && (x||y)){
        if(x>y)swap(x,y);
        bool ok=true;
        for(int i=x; i<=y&&ok; ++i)if(!prime[i*i+i+41])ok=false;
        if(ok)cout<<"OK\n";
        else cout<<"Sorry\n";
    }
}